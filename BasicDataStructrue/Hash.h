#pragma once
// ����ɢ�к���
typedef int Type;
//size_t hash(Type k) {
//	size_t  m = 701;
//	return k / m;
//}
//�˷�ɢ�к���
size_t hash(Type k) {
	size_t m = 1024;
	double A = 0.6180339887, t;
	size_t h = k * A;
	t = k * A - h;
	return m * t;
}

