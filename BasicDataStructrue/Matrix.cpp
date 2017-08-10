const size_t vertexNum = 10;
const size_t edgeNum = 10;
size_t Graph[vertexNum][vertexNum];
int value[2 * edgeNum];
const size_t L = 2 * edgeNum / 8 + 1;
unsigned char bitMap[L];

void SetBit(size_t index) {
	size_t i = index / 8, j = index % 8;
	unsigned char a = 1 << j;
	bitMap[i] = bitMap[i] | a;
}
void ResetBit(size_t index) {
	size_t i = index / 8, j = index % 8;
	unsigned char a = 1 << 8 - 1;
	a = a - 1 << j;
	bitMap[i] = bitMap[i] & a;
}
void init() {
	for (size_t i = 0; i != vertexNum; ++i)
		for (size_t j = 0; j != vertexNum; ++j)
			Graph[i][j] = 0;
	size_t counter = 2 * edgeNum;
	for (size_t i = 0; i != counter; ++i)
		value[i] = 0;
	for (size_t i = 0; i != L; ++i)
		bitMap[i] = (1 << 8) - 1;
	ResetBit(0);
}
size_t FindEmpty() {
	unsigned char a, b;
	for (size_t i = 0; i != L; ++i) {
		if (a = bitMap[i]) {
			for (size_t j = 0; j != 8; ++j) 
			{
				b = 1 << j;
				if (b = b & a)
					return i * 8 + j;
			}
		}
	}
}