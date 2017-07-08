#ifndef LINK_LIST_H
#define LINK_LIST_H
#include<string>
#include<iostream>
typedef std::string T1;
class LinkList{	
public:
	LinkList();
	~LinkList(){ clearUp(); delete NIL; };
	void push(const T1& e);
	T1 pop(const T1 &e);
	T1 find(const T1 &e);
	bool empty() const;
	size_t size() const;
private:
	struct ElementType{
		T1 data;
		ElementType *predecessor;
		ElementType *successor;
	};
	ElementType *NIL;
	size_t elementCnt;
	ElementType *search(const T1& e);
	void buildLink(ElementType *predece, ElementType *succ);
	void clearUp();
	LinkList(const LinkList &lis) = delete;
	LinkList& operator=(const LinkList &lis) = delete;
};
//************************************************
bool LinkList::
empty() const {
	if (elementCnt == 0)
		return true;
	return false;
}
//*************************************************
size_t LinkList::
size() const {
	return elementCnt;
}
//*************************************************
T1 LinkList::
find(const T1 &e) {
	ElementType *temp = search(e);
	if (temp == NIL) {
		//std::cout << "the data you are searching doesn't exist" << std::endl;
		return T1();
	}
	return  T1(temp->data);
}
//***************************************************
LinkList::
LinkList()
: NIL(nullptr), elementCnt(0)
{
	NIL = new ElementType();
}
//***************************************************
void LinkList::
push(const T1& e){
	ElementType *newElement = new ElementType{ e, nullptr, nullptr };
	if (elementCnt == 0) {
		NIL->successor = newElement;
		newElement->predecessor = newElement;
		newElement->successor = newElement;
		++elementCnt;
		return;
	}	                                                             ////
	ElementType *temp = NIL->successor, *predece = temp->predecessor;
	buildLink(predece, newElement);
	buildLink(newElement, temp);
	++elementCnt;
}
//****************************************************
void LinkList::
buildLink(ElementType *predece,ElementType *succ){
	predece->successor = succ;
	succ->predecessor = predece;
}
//****************************************************
LinkList::
ElementType *LinkList::
search(const T1 &e){
	ElementType *tempB = NIL->successor, *p = tempB->predecessor;
	while (p != tempB && p->data != e)
		p = p->predecessor;
	if (p == tempB) {
		if (p->data != e)
			return NIL;                                                                     //没找到
	}
	return p;
}
//******************************************************
T1 LinkList::
pop(const T1 &e){
	if (elementCnt == 0)
		return	T1();                                                                      //没找到
	ElementType *temp = search(e);
	if (temp == NIL)
		return T1();                                                                       // 没找到
	T1 ret = temp->data;
	ElementType *succ = temp->successor, *predece = temp->predecessor;
	if (temp == NIL->successor) {
		if (elementCnt == 1)
			NIL->successor = nullptr;
		else
			NIL->successor = predece;
	}
	buildLink(predece, succ);
	--elementCnt;
	delete temp;
	return ret;
}
//********************************************************
void LinkList::
clearUp(){
	ElementType *end = NIL->successor, *p = end;
	if (elementCnt <= 1) {
		delete p;
		return;
	}	
	ElementType *temp = p->successor;
	//std::cout << "deleting " << p->data << std::endl;
	delete p;
	p = temp;
	while (p != end){
		temp = p->successor;
		//std::cout << "deleting " << p->data << std::endl;                                  //
		delete p;
		p = temp;
	}
}
#endif