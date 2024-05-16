#include"AES.h"

vector<Byte> HToB(string s) {
	int size = s.size() / 2;
	vector<Byte> temp;
	for (int i = 0; i < size; i++) {
		int a, b;
		if (s[2 * i] > 47 && s[2 * i] < 58) {
			a = s[2 * i] - 48;
		}
		else {
			a = s[2 * i] - 87;
		}
		if (s[2 * i + 1] > 47 && s[2 * i + 1] < 58) {
			b = s[2 * i + 1] - 48;
		}
		else {
			b = s[2 * i + 1] - 87;
		}
		bitset<4> abit = bitset<4>(a), bbit = bitset<4>(b);
		temp.push_back(Byte(abit.to_string() + bbit.to_string()));
	}
	return temp;
}

string BToH(vector<Byte> b) {
	int size = b.size();
	string h;
	string highChar, lowChar;
	for (int i = 0; i < size; i++) {
		bitset<4> high = bitset<4>(b[i].to_string().substr(0, 4)), low = bitset<4>(b[i].to_string().substr(4, 4));
		int highInt = high.to_ulong(), lowInt = low.to_ulong();
		if (highInt < 10) {
			highChar = highInt + 0x30;
		}
		else {
			highChar = highInt + 0x57;
		}
		if (lowInt < 10) {
			lowChar = lowInt + 0x30;
		}
		else {
			lowChar = lowInt + 0x57;
		}
		h += highChar + lowChar + " ";
	}
	return h;
}

vector<Byte> operator ^ (vector<Byte> a, vector<Byte> b) {
	for (int i = 0; i < a.size(); i++) {
		a[i] = a[i] ^ b[i];
	}
	return a;
}

vector<Byte> Cut(vector<Byte> a, int start, int length) {
	vector<Byte> result;
	for (int i = 0; i < length; i++)	result.push_back(a[start + i]);
	return result;
}

vector<Byte> SubByte(vector<Byte> b) {
	for (int i = 0; i < 4; i++) {
		int temp = b[i].to_ulong(), row, col;
		row = temp / 16;
		col = temp % 16;
		b[i] = Byte(SBox[row][col]);
	}
	return b;
}

MessageStream::MessageStream(string s, string k, bool Hex, bool p) {
	padding = p;
	if (Hex) {
		stream = HToB(s);
		key = HToB(k);
		return;
	}
	for (int i = 0; i < s.size(); i++) {
		stream.push_back(Byte(s[i]));
	}
	for (int i = 0; i < 16; i++) {
		key.push_back(Byte(k[i]));
	}
}

void MessageStream::Print() {
	for (int i = 0; i < stream.size(); i++) {
		cout << stream[i];
	}
	cout << endl;
}

vector<Byte> MessageStream::Getter() {
	return stream;
}

void MessageStream::Padding() {
	int size = stream.size();
	if (size % 16 != 12) {
		int padding = 12 - size < 0 ? 12 - size + 16 : 12 - size;
		for (int i = 0; i < padding; i++) stream.push_back(Byte(0));
	}
	bitset<32> length(size);
	stream.push_back(Byte(length.to_string().substr(0, 8)));
	stream.push_back(Byte(length.to_string().substr(8, 8)));
	stream.push_back(Byte(length.to_string().substr(16, 8)));
	stream.push_back(Byte(length.to_string().substr(24, 8)));
}

int MessageStream::BytesToInt(vector<Byte> b) {
	int result = 0, size = b.size();
	for (int i = 0; i < b.size(); i++) {
		result += b[i].to_ulong() * pow(256, size - i - 1);
	}
	return result;
}

vector<Byte> MessageStream::TFunction(vector<Byte> b, int i) {
	Byte temp = b[0];
	vector<Byte> ron;
	b[0] = b[1];	b[1] = b[2];	b[2] = b[3];	b[3] = temp;
	b = SubByte(b);
	switch (i) {
	case 0:ron.push_back(Byte(1));	break;
	case 1:ron.push_back(Byte(2));	break;
	case 2:ron.push_back(Byte(4));	break;
	case 3:ron.push_back(Byte(8));	break;
	case 4:ron.push_back(Byte(16));	break;
	case 5:ron.push_back(Byte(32));	break;
	case 6:ron.push_back(Byte(64));	break;
	case 7:ron.push_back(Byte(128));	break;
	case 8:ron.push_back(Byte(27));	break;
	case 9:ron.push_back(Byte(54));	break;
	}
	for (int c = 0; c < 3; c++)
		ron.push_back(Byte(0));
	b = b ^ ron;
	return b;
}

vector<vector<Byte>> MessageStream::RoundKeyGeneration() {
	roundKey.resize(44);
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			roundKey[i].push_back(key[4 * i + j]);
	for (int i = 1; i < 11; i++) {
		roundKey[4 * i] = roundKey[4 * i - 4] ^ TFunction(roundKey[4 * i - 1], i - 1);
		roundKey[4 * i + 1] = roundKey[4 * i - 3] ^ roundKey[4 * i];
		roundKey[4 * i + 2] = roundKey[4 * i - 2] ^ roundKey[4 * i + 1];
		roundKey[4 * i + 3] = roundKey[4 * i - 1] ^ roundKey[4 * i + 2];
	}
	return roundKey;
}
vector<Byte> MessageStream::AESEnc() {
	vector<Byte> result;
	if (padding)
		Padding();
	RoundKeyGeneration();
	int size = stream.size() / 16;
	for (int i = 0; i < size; i++) {
		Matrix matrix(Cut(stream, 16 * i, 16), roundKey);
		matrix.AddRoundKey(0);
		for (int j = 0; j < 9; j++) {
			matrix.SubByte();
			matrix.ShiftRows();
			matrix.MixColumns();
			matrix.AddRoundKey(j + 1);
		}
		matrix.SubByte();
		matrix.ShiftRows();
		matrix.AddRoundKey(10);
		for (int k = 0; k < 16; k++)	result.push_back(matrix.Getter()[k]);
	}
	stream = result;
	roundKey = {};
	return result;
}

vector<Byte> MessageStream::AESDec() {
	vector<Byte> result, c, temp;
	RoundKeyGeneration();
	int size = stream.size() / 16;
	for (int i = 0; i < size; i++) {
		Matrix matrix(Cut(stream, 16 * i, 16), roundKey);
		matrix.AddRoundKey(10);
		for (int j = 0; j < 9; j++) {
			matrix.InverseShiftRows();
			matrix.InverseSubByte();
			matrix.AddRoundKey(9 - j);
			matrix.InverseMixColumns();
		}
		matrix.InverseShiftRows();
		matrix.InverseSubByte();
		matrix.AddRoundKey(0);
		for (int k = 0; k < 16; k++)	result.push_back(matrix.Getter()[k]);
	}
	if (padding) {
		c.assign(result.end() - 4, result.end());
		int length = BytesToInt(c);
		int a = 0;
		a += 1;
		stream.assign(result.begin(), result.begin() + length);
	}
	else {
		stream = result;
	}
	
	roundKey = {};
	return result;
}

Matrix::Matrix(vector<Byte> stream, vector<vector<Byte>> rk) {
	for (int i = 0; i < stream.size(); i++) {
		m[i / 4][i % 4] = stream[i];
	}
	roundKey = rk;
}
Byte Matrix::GFMul(int a, int f) {
	if (a == 2)			return Mul_02[f];
	else if (a == 3)	return Mul_03[f];
	else if (a == 9)	return Mul_09[f];
	else if (a == 11)	return Mul_0b[f];
	else if (a == 13)	return Mul_0d[f];
	else if (a == 14)		return Mul_0e[f];
}
void Matrix::SubByte() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int temp = m[j][i].to_ulong(), row, col;
			row = temp / 16;
			col = temp % 16;
			m[j][i] = SBox[row][col];
		}
	}
}
void Matrix::ShiftRows() {
	Byte temp;
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < i; j++) {
			temp = m[3][i];
			m[3][i] = m[0][i];
			m[0][i] = m[1][i];
			m[1][i] = m[2][i];
			m[2][i] = temp;
		}
	}
}
void Matrix::MixColumns() {
	array<Byte, 4> arr;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			arr[j] = m[i][j];
		m[i][0] = GFMul(0x02, arr[0].to_ulong()) ^ GFMul(0x03, arr[1].to_ulong()) ^ arr[2] ^ arr[3];
		m[i][1] = arr[0] ^ GFMul(0x02, arr[1].to_ulong()) ^ GFMul(0x03, arr[2].to_ulong()) ^ arr[3];
		m[i][2] = arr[0] ^ arr[1] ^ GFMul(0x02, arr[2].to_ulong()) ^ GFMul(0x03, arr[3].to_ulong());
		m[i][3] = GFMul(0x03, arr[0].to_ulong()) ^ arr[1] ^ arr[2] ^ GFMul(0x02, arr[3].to_ulong());
	}
}
void Matrix::AddRoundKey(int a) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			m[i][j] = m[i][j] ^ roundKey[4 * a + i][j];
}
void Matrix::InverseSubByte() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int temp = m[j][i].to_ulong(), row, col;
			row = temp / 16;
			col = temp % 16;
			m[j][i] = InverseSBox[row][col];
		}
	}
}
void Matrix::InverseShiftRows() {
	Byte temp;
	for (int i = 1; i < 4; i++) {
		for (int j = 0; j < i; j++) {
			temp = m[0][i];
			m[0][i] = m[3][i];
			m[3][i] = m[2][i];
			m[2][i] = m[1][i];
			m[1][i] = temp;
		}
	}
}
void Matrix::InverseMixColumns() {
	array<Byte, 4> arr;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
			arr[j] = m[i][j];

		m[i][0] = GFMul(0x0e, arr[0].to_ulong()) ^ GFMul(0x0b, arr[1].to_ulong()) ^ GFMul(0x0d, arr[2].to_ulong()) ^ GFMul(0x09, arr[3].to_ulong());
		m[i][1] = GFMul(0x09, arr[0].to_ulong()) ^ GFMul(0x0e, arr[1].to_ulong()) ^ GFMul(0x0b, arr[2].to_ulong()) ^ GFMul(0x0d, arr[3].to_ulong());
		m[i][2] = GFMul(0x0d, arr[0].to_ulong()) ^ GFMul(0x09, arr[1].to_ulong()) ^ GFMul(0x0e, arr[2].to_ulong()) ^ GFMul(0x0b, arr[3].to_ulong());
		m[i][3] = GFMul(0x0b, arr[0].to_ulong()) ^ GFMul(0x0d, arr[1].to_ulong()) ^ GFMul(0x09, arr[2].to_ulong()) ^ GFMul(0x0e, arr[3].to_ulong());
	}
}
vector<Byte> Matrix::Getter() {
	vector<Byte> temp;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			temp.push_back(m[i][j]);
	return temp;
}
void Matrix::Print() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			cout << m[j][i];
}

int main() {
	string message, key;
	int hex, padding;
	cout << "明文是否填充？(1 是；0 不是)";
	cin >> padding;
	cout << "明文和密钥是否为十六进制？(1 是；0 不是)";
	cin >> hex;
	cout << "请输入明文:";
	cin >> message;
	cout << "请输入密钥:";
	cin >> key;
	MessageStream a(message, key, hex, padding);
	a.AESEnc();
	cout << "密文(B)为:";
	a.Print();
	cout << "密文(H)为:" << BToH(a.Getter()) << endl;
	a.AESDec();
	cout << "解密(B)为:";
	a.Print();
	if (hex) {
		cout << "明文(H)为:" << BToH(a.Getter()) << endl;
	}
	else {
		cout << "明文为:";
		for (int i = 0; i < a.Getter().size(); i++)	cout << (char)a.Getter()[i].to_ulong();
		cout << endl;
	}
}

//3243f6a8885a308d313198a2e0370734
//2b7e151628aed2a6abf7158809cf4f3c