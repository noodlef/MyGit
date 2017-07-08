#include"Queue.h"
#include"Sort.h"
#include<string>
#include<iostream>
#include<fstream>
using namespace std;
class A {
	int i;
public:
	class A_class {
	public:
		int i;
	};
	virtual void f(void) {
		std::cout << "A_f" << std::endl;
	}
	~A() { f(); }
};
class B :public A{

public:
	class A_class {
	public:
		int j;
	};
	void f() {
		std::cout << "B_f" << std::endl;
	}
	void d() { t.j; }
private:
	int i;
	A_class t;
};
void f() {
	const int sz = 100;
	const int *v = &sz;
	int f[sz];
}
template<class T, int size = 20>
class arry {
	int a[size];
};
bool compare(int lhs, int rhs) {
	if (lhs > rhs)
		return true;
	else
		return false;
}
int main()
{

		///*Data d[10] = { { 1 }, { 2 }, { 5 }, { 8,"wow" }, { 4 }, { 6 }, { 7 }, { 0 }, { 9 }, { 3 } }, temp;*/
	 //   Data t[10000];
		//for (int i = 0; i != 10000; ++i) {
		//	t[i].key = i;
		//}
		//RedBlackTree tree;   
		//for (int i = 0; i != 10; ++i) {
		//	tree.add(t[i]);
		//}
		////temp = tree.predecessorKey(9);
		////std::cout << temp.key << " " << temp.p << std::endl;
		//print(cout, tree);
	    Queue<int> q;
	
	    for (int i = 0; i != 10; ++i) {
		       q.push_back(i);
	    }
		templa::quickSort(q.begin(), q.end(), compare);
		for (int i = 0; i != 10; ++i) {
			std::cout << q[i] << std::endl;
		}
	    system("pause");
	    return 0;
}