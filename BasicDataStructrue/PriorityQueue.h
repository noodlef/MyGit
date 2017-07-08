// 使用二叉堆实现的优先队列
// 模版中的参数Flag 表示 优先级比较规则
// 默认情况下关键字越大， 优先级越高；
// 如果设置 Flag = 'm',则表示关键字越小，优先级越高
// 关键字类型要有 operator> 函数 ， 和 operator + 函数；
// 如果没有一定要到 bigger() 函数 和 incrementKey() 函数里面进行相应的修改
#pragma once
#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include<iostream>
#include"Data.h"
template<typename T1, typename T2, char Flag = 'M'>
class PriorityQueue {
public:
	typedef  T1 KeyType;
	typedef  T2 SatalliteData;
	PriorityQueue() : size(0), elementCnt(0), ptr(nullptr) { }
	PriorityQueue(const Data<T1, T2> *b, const Data<T1, T2> *e);
	void add(const KeyType &k, const SatalliteData &d);
	void add(const Data<T1, T2> &e);
	bool empty();	
	Data<T1, T2> maximum();
	Data<T1, T2> minimum();
	Data<T1, T2> extractMax();
	Data<T1, T2> extractMin();
	void incrementKey(const SatalliteData &d, const KeyType &increment);                    // 增加key值
	void setKey(const SatalliteData &d,const KeyType &k);                                   // 重新设定key值
	size_t Size() const { return elementCnt; }
	~PriorityQueue() { delete[] ptr; };
private:
	PriorityQueue(const PriorityQueue &q) = delete;                                         //禁止拷贝构造
	PriorityQueue& operator=(const PriorityQueue &q) = delete;                              //禁止拷贝赋值
	struct ElementType {
		KeyType key;                                                                      
		SatalliteData element;
	};
	void malloc();
	size_t find(const SatalliteData &d);
	void shiftUp(int index);
	void shiftDown(int index);
	void push(const ElementType *e);
	bool bigger(const ElementType *lhs, const ElementType *rhs) const;
	void swap(ElementType *lhs, ElementType *rhs);	
	size_t size;                                                                              //分配空间的大小
	size_t elementCnt;                                                                       // 实际存取的元素的个数
	ElementType *ptr;
};
//************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
bool PriorityQueue<T1, T2, Flag>::
empty() {
	if (elementCnt == 0)
		return true;
	else
		return false;
}
//*************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
void PriorityQueue<T1, T2, Flag>::
add(const KeyType &k, const SatalliteData &d) {
	Data<T1, T2> e{ k, d };
	add(e);
}
//*************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
inline
bool PriorityQueue<T1, T2, Flag>::
bigger(const ElementType *lhs, const ElementType *rhs) const{
	if (Flag == 'M')
		return lhs->key > rhs->key;//lhs->key > rhs->key 大顶堆
	else
		return !(lhs->key > rhs->key);
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
void PriorityQueue<T1, T2, Flag>::
swap(ElementType *lhs, ElementType *rhs){
	ElementType temp;
	temp = *lhs;
	*lhs = *rhs;
	*rhs = temp;
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
void PriorityQueue<T1, T2, Flag>::
malloc(){
	int newSize;
	if (size == 0)
		newSize = 1;
	else
		newSize = size * 2;
	//int increment = 2;
	//int newSize = size + increment;
	ElementType *newPtr = new ElementType[newSize];
	ElementType *temp1 = newPtr, *temp2 = ptr;
	for (int i = 0; i != elementCnt; ++i)
		*temp1++ = *temp2++;
	delete[] ptr;
	ptr = newPtr;
	size = newSize;
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
void PriorityQueue<T1, T2, Flag>::
shiftUp(int index){
	int parent = index / 2, child = index;
	while (child > 1){
		if (bigger(ptr + child - 1, ptr + parent - 1)){
			swap(ptr + child - 1, ptr + parent - 1);
			child = parent;
			parent = child / 2;
		}
		else
			return;
	}
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
void PriorityQueue<T1, T2, Flag>::
shiftDown(int index){
	int parent = index, heapSize = elementCnt;
	int lchild = 2 * parent, rchild = lchild + 1, mark;
	while (parent <= heapSize / 2){
		if (bigger(ptr + lchild - 1, ptr + parent - 1))
			mark = lchild;
		else
			mark = parent;
		if (rchild <= heapSize && bigger(ptr + rchild - 1, ptr + mark - 1))
			mark = rchild;
		if (mark != parent){
			swap(ptr + mark - 1, ptr + parent - 1);
			parent = mark;
			lchild = parent * 2;
			rchild = lchild + 1;
		}
		else
			return;
	}
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
void PriorityQueue<T1, T2, Flag>::
push(const ElementType *e){
	if (elementCnt == size)
		malloc();
	*(ptr + elementCnt) = *e;
	++elementCnt;
	shiftUp(elementCnt);
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
void PriorityQueue<T1, T2, Flag>::
add(const Data<T1, T2> &e){
	ElementType d{ e.key, e.element };
	push(&d);
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
PriorityQueue<T1, T2, Flag>::
PriorityQueue(const Data<T1, T2> *b, const Data<T1, T2> *e)
	: size(0), elementCnt(0), ptr(nullptr)
{
	for (auto beg = b; beg != e; ++beg)
		add(*beg);

}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
Data<T1, T2> PriorityQueue<T1, T2, Flag>::
maximum(){
	if (elementCnt == 0) {
		std::cout << "empty heap " << std::endl;
		return Data<T1, T2>();                                         //默认构造函数
	}
	Data<T1, T2> ret = { ptr->key, ptr->element };
	return ret;
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
Data<T1, T2> PriorityQueue<T1, T2, Flag>::
minimum() {
	Data<T1, T2> ret = maximum();
	return ret;
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
Data<T1, T2> PriorityQueue<T1, T2, Flag>::
extractMax(){
	if (elementCnt == 0){
		std::cout << "heap underflow" << std::endl;
		return Data<T1, T2>();                                        // 默认构造函数
	}
	Data<T1, T2> ret = {ptr->key, ptr->element};
	*ptr = *(ptr + elementCnt - 1);
	--elementCnt;
	shiftDown(1);
	return ret;
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
Data<T1, T2> PriorityQueue<T1, T2, Flag>::
extractMin() {
	Data<T1, T2> ret = extractMax();
	return ret;
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
size_t PriorityQueue<T1, T2, Flag>::
find(const SatalliteData &d){
	int ret;
	for (int i = 0; i != elementCnt; ++i){
		if (d == (ptr + i)->element){
			ret = i + 1;
			return ret;
		}
	}
	return 0;
}
//**************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
void PriorityQueue<T1, T2, Flag>::
incrementKey(const SatalliteData &d, const KeyType &increment){
	size_t targetIndex = find(d);
	if (targetIndex == 0){
		std::cout << "the element doesn't exist" << std::endl;
		return;
	}
	ElementType oldValue = *(ptr + targetIndex - 1);                             //关键字类型要有 operator+ 函数， operator> 函数
	(ptr + targetIndex - 1)->key += increment;
	if (bigger(ptr + targetIndex - 1, &oldValue))
		shiftUp(targetIndex);
	else
		shiftDown(targetIndex);
}
//***************************************************************************
template<typename T1, typename T2, char Flag = 'M'>
void PriorityQueue<T1, T2, Flag>::
setKey(const SatalliteData &d, const KeyType &k) {
	size_t targetIndex = find(d);
	if (targetIndex == 0) {
		std::cout << "the element doesn't exist" << std::endl;
		return;
	}
	ElementType oldValue = *(ptr + targetIndex - 1);                             //关键字类型要有 operator+ 函数， operator> 函数
	//(ptr + targetIndex - 1)->key += increment;
	(ptr + targetIndex - 1)->key = k;
	if (bigger(ptr + targetIndex - 1, &oldValue))
		shiftUp(targetIndex);
	else
		shiftDown(targetIndex);
}
#endif