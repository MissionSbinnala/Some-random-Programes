#include"SM3.h"

static DWord operator << (DWord a, int n) {		//重载循环左移
	for (int i = 0; i < n % 32; i++) {
		bool high = a[31];
		a <<= 1;
		a[0] = high;
	}
	return a;
}

string BToH(DWord b) {
	string h;
	char c;
	for (int i = 0; i < 8; i++) {
		bitset<4> hex = bitset<4>(b.to_string().substr(4 * i, 4));
		int hexN = hex.to_ulong();
		if (hexN < 10) {
			c = hexN + 0x30;
		}
		else {
			c = hexN + 0x57;
		}
		h += c;
	}
	return h;
}

Message::Message(string s) {
	for (int i = 0; i < s.size(); i++) {
		stream.push_back(Byte(s[i]));
	}
	A = DWord("01110011100000000001011001101111"), B = DWord("01001001000101001011001010111001"),
		C = DWord("00010111001001000100001011010111"), D = DWord("11011010100010100000011000000000"),
		E = DWord("10101001011011110011000010111100"), F = DWord("00010110001100010011100010101010"),
		G = DWord("11100011100011011110111001001101"), H = DWord("10110000111110110000111001001110");
	Padding();
	Vector[0] = A; Vector[1] = B; Vector[2] = C; Vector[3] = D;
	Vector[4] = E; Vector[5] = F; Vector[6] = G; Vector[7] = H;
}

void Message::Padding() {
	int size = stream.size() % 64;
	bitset<64> length(stream.size() * 8);
	int padding = (55 - size) % 64;
	stream.push_back(Byte(128));
	for (int i = 0; i < padding; i++) stream.push_back(Byte(0));
	for (int i = 0; i < 8; i++) { stream.push_back(Byte(length.to_string().substr(8 * i, 8))); }
}

void Message::DisplayVector() {
	cout << endl << "加密结果为：";
	for (int i = 0; i < 8; i++)	cout << BToH(Vector[i]) << " ";
	cout << endl;
}

void Message::Merge(int n) {
	for (int i = 0; i < 16; i++) {
		string s;
		s += stream[64 * n + 4 * i].to_string();
		s += stream[64 * n + 4 * i + 1].to_string();
		s += stream[64 * n + 4 * i + 2].to_string();
		s += stream[64 * n + 4 * i + 3].to_string();
		W[i] = DWord(s);
	}
}

void Message::WExpension() {
	for (int i = 16; i < 68; i++) {
		W[i] = P1(W[i - 16] ^ W[i - 9] ^ (W[i - 3] << 15)) ^ (W[i - 13] << 7) ^ W[i - 6];
	}
	for (int i = 0; i < 64; i++) {
		WDot[i] = W[i] ^ W[i + 4];
	}
}

DWord Message::P1(DWord w) {
	return (w ^ (w << 15) ^ (w << 23));
}

DWord Message::P0(DWord w) {
	return (w ^ (w << 9) ^ (w << 17));
}

DWord Message::FF1(DWord x, DWord y, DWord z) {
	return (x ^ y ^ z);
}

DWord Message::FF2(DWord x, DWord y, DWord z) {
	return ((x & y) | (x & z) | (y & z));
}

DWord Message::GG2(DWord x, DWord y, DWord z) {
	return ((x & y) | (~x & z));
}

void Message::CompressFunction() {
	DWord SS1, SS2, T, TT1, TT2;
	T = DWord("01111001110011000100010100011001");
	A = Vector[0]; B = Vector[1]; C = Vector[2]; D = Vector[3];
	E = Vector[4]; F = Vector[5]; G = Vector[6]; H = Vector[7];
	for (int i = 0; i < 16; i++) {
		SS1 = DWord(((A << 12).to_ulong() + E.to_ulong() + (T << i).to_ulong())) << 7;
		SS2 = DWord(SS1 ^ (A << 12));
		TT1 = DWord(FF1(A, B, C).to_ulong() + D.to_ulong() + SS2.to_ulong() + WDot[i].to_ulong());
		TT2 = DWord(FF1(E, F, G).to_ulong() + H.to_ulong() + SS1.to_ulong() + W[i].to_ulong());
		D = C;
		C = B << 9;
		B = A;
		A = TT1;
		H = G;
		G = F << 19;
		F = E;
		E = P0(TT2);
	}
	T = DWord("01111010100001111001110110001010");
	for (int i = 16; i < 64; i++) {
		SS1 = DWord(((A << 12).to_ulong() + E.to_ulong() + (T << i).to_ulong())) << 7;
		SS2 = DWord(SS1 ^ (A << 12));
		TT1 = DWord(FF2(A, B, C).to_ulong() + D.to_ulong() + SS2.to_ulong() + WDot[i].to_ulong());
		TT2 = DWord(GG2(E, F, G).to_ulong() + H.to_ulong() + SS1.to_ulong() + W[i].to_ulong());
		D = C;
		C = B << 9;
		B = A;
		A = TT1;
		H = G;
		G = F << 19;
		F = E;
		E = P0(TT2);
	}
	Vector[0] = A ^ Vector[0];
	Vector[1] = B ^ Vector[1];
	Vector[2] = C ^ Vector[2];
	Vector[3] = D ^ Vector[3];
	Vector[4] = E ^ Vector[4];
	Vector[5] = F ^ Vector[5];
	Vector[6] = G ^ Vector[6];
	Vector[7] = H ^ Vector[7];
}

void Message::SM3() {
	int size = stream.size() / 64;
	for (int i = 0; i < size; i++) {
		Merge(i);
		WExpension();
		CompressFunction();
	}
	A = DWord("01110011100000000001011001101111"), B = DWord("01001001000101001011001010111001"),
		C = DWord("00010111001001000100001011010111"), D = DWord("11011010100010100000011000000000"),
		E = DWord("10101001011011110011000010111100"), F = DWord("00010110001100010011100010101010"),
		G = DWord("11100011100011011110111001001101"), H = DWord("10110000111110110000111001001110");
	DisplayVector();
}