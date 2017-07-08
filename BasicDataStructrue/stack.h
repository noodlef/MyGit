#pragma once
#ifndef STACK_H
#define STACK_H
#include<iostream>
namespace templa {
	template<typename T1>
	class Stack {
	public:
		Stack();
		~Stack() { delete[] stackBottom; };
		bool stackEmpty();
		void push(const T1 &e);
		T1 pop();
		size_t size() const { return elementCnt; }
		T1 top() const { return *(ptr - 1); }                                  // 返回栈顶元素
		T1 bottom() const { return *stackBottom; }                             // 返回栈底元素
	private:
		T1 *ptr;                                                               
		T1 *stackBottom;                                                        // 栈底
		size_t elementCnt;                                                      // 包含元素个数
		size_t sz;                                                              // 分配的空间大小
		void malloc();
		void free();
		Stack(const Stack &s) = delete;                                         // 禁止拷贝构造
		Stack& operator=(const Stack &s) = delete;                              // 禁止拷贝复制
	};
	//*****************************************************
	template<typename T1>
	bool Stack<T1>::stackEmpty() {
		if (elementCnt == 0)
			return true;
		return false;
	}
	//*****************************************************
	template<typename T1>
	Stack<T1>::Stack()
		:ptr(nullptr), stackBottom(nullptr), elementCnt(0), sz(0)
	{
		sz = 2;
		T1 *temp = new T1[sz];                                                  //默认构造函数
		stackBottom = temp;
		ptr = stackBottom;
	}
	//******************************************************
	template<typename T1>
	void Stack<T1>::
		push(const T1 &e) {
		if (sz <= elementCnt + 1)
			malloc();
		*ptr = e;
		++ptr;
		++elementCnt;
	}
	//*****************************************************
	template<typename T1>
	T1 Stack<T1>::
		pop() {
		if (elementCnt == 0) {
			return T1();
			std::cout << "stack underflow" << std::endl;
		}                                                                       // 默认构造函数  
		--ptr;
		T1 ret = *ptr;
		--elementCnt;
		free();
		return ret;
	}
	//****************************************************
	template<typename T1>
	void Stack<T1>::
		malloc() {
		//std::cout << "malloc()" << " " << sz << std::endl;
		size_t newSize = sz * 2;
		T1 *newStackBottom = new T1[newSize];                                   // 默认构造函数
		T1 *temp1 = newStackBottom, *temp2 = stackBottom;
		for (int i = 0; i != elementCnt; ++i)
			*temp1++ = *temp2++;                                                 // 有点小问题
		delete[] stackBottom;
		stackBottom = newStackBottom;
		ptr = temp1;
		sz = newSize;
	};
	//******************************************************
	// 当栈中元素个数只有给栈分配容量的1/4时，就释放当前容量的1/2
	template<typename T1>
	void Stack<T1>::
		free() {
		if (4 * (elementCnt + 1) <= sz) {
			//std::cout << "free memory sz = " << sz << std::endl;
			sz /= 4;
			malloc();
		}
	}
}
#endif