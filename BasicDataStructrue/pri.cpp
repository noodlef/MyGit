#include<iostream>
#include"pri.h"
#include<string>
using namespace std;
int main() {
	PriorityQueue<std::string, int,'m'> q;
	for (int i = 0; i != 10; ++i) {
		std::string s(i + 1, 's');
		q.add(s, i);
	}
	q.incrementKey(1, "a");
	for (int i = 0; i != 10; ++i) {
		cout << q.extractMin().key << endl;
	}
	q.maximum();
	q.minimum();
	q.extractMax();
	q.extractMin();
	q.Size();
	system("pause");
	return 0;
}