// 先进先出队列
// 使用双联表实现
#pragma once
#ifndef ENQUEUE_H
#define ENQUEUE_H
#include"LinkList.h"
namespace templa {
	using templa::LinkList;
	template<typename T1>
	class Enqueue : private LinkList<T1> {
	public:
		T1 pop();
		void push(const T1& e) {
			LinkList<T1>::push_back(e);
		}
		bool empty() {
			return LinkList<T1>::empty();
		}
	};

	template<typename T1>
	T1 Enqueue<T1>::
		pop() {
		T1 ret = LinkList<T1>::pop_front();
		return ret;
	}
}
#endif