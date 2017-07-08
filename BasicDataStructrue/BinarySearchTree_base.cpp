#include"BinarySearchTree_base.h"
using namespace Tree;
//*************************************************************
std::ostream& Tree::
print(std::ostream &os, const BinarySearchTree &tree)
{
	BinarySearchTree::ElementType *p = tree.root;
	os << "中序遍历" << std::endl;
	tree.inorderTreeWalk(p);
	return os;
}
//***************************************************************
void BinarySearchTree::
inorderTreeWalk(const ElementType *p) const {
	if (p == nil) {
		std::cout << "empty tree" << std::endl;
		return;
	}
	while (true) {
		while (p->lchild != nil)
			p = p->lchild;
		print(std::cout, p);
		if (p->rchild != nil)
			p = p->rchild;
		else
		{
		     while (true) {
				if (p->parent == nil)
					return;
				if (p == p->parent->lchild) {
					p = p->parent;
					print(std::cout, p);
					if (p->rchild != nil) {
						p = p->rchild;
						break;
					}
				}
				else
					p = p->parent;
			}
		}
	}
}
//*****************************************************************
std::ostream& BinarySearchTree::
print(std::ostream &os, const ElementType *e) const {
	os << "key " << e->key << " is ";
	if (e->parent != nil) {
		if (e->parent->lchild == e)
			os << " " << "left child of key " << e->parent->key << std::endl;
		else
			os << " " << "right child of key " << e->parent->key << std::endl;
	}
	else
		os << "root" << std::endl;
	return os;
}
//******************************************************************
BinarySearchTree::
BinarySearchTree() {
	treeSize = 0;
	nil = new ElementType();                                      //默认构造函数
	root = nil;
}
//*******************************************************************
Data BinarySearchTree::
searchKey(KeyType k) const {
	ElementType *temp = search(k);
	if (temp == nil)
		return Data();                                            //抛出异常
	return Data{ temp->key, temp->p };
}
//*******************************************************************
Data BinarySearchTree::
maximumKey() const
{
	ElementType *temp = maximum(root);
	if (temp == nil)
		return Data();                                           //抛出异常
	else
		return Data{ temp->key, temp->p };
}
//*********************************************************************
Data BinarySearchTree::
minimumKey() const{
	ElementType *temp = minimum(root);
	if (temp == nil)
		return Data();                                         //抛出异常
	else
		return Data{ temp->key, temp->p };
}
//**********************************************************************
Data BinarySearchTree::
predecessorKey(KeyType k) const{
	ElementType *t = search(k), *temp;
	temp = predecessor(t);
	if (temp == nil)
		return Data();                                        //抛出异常
	else
		return Data{ temp->key, temp->p };
}
//**********************************************************************
Data BinarySearchTree::
successorKey(KeyType k) const{
	ElementType *t = search(k), *temp;
	temp = successor(t);
	if (temp == nil)
		return Data();                                        //抛出异常
	else
		return Data{ temp->key, temp->p };
}
//**********************************************************************
BinarySearchTree::ElementType::
ElementType(KeyType k, SatalliteData s, Color col)
	: key(k), p(s), color(col) { }
//**********************************************************************
void BinarySearchTree::
add(const Data &dat) {
	ElementType *temp = search(dat.key);
	if (temp != nil) {
		std::cout << "The Key(" << dat.key << ")has already existed" << std::endl;
		return;
	}
	ElementType e(dat.key, dat.p);                                            //构造函数
	insert(e);
}
//***********************************************************************
void BinarySearchTree::
insert(const ElementType &e) {
	ElementType *z = new ElementType(e.key, e.p);               //构造函数
	ElementType *p = root, *temp = nil;
	set(z);                                                    // 设置z 的指针
	while (p != nil) {
		temp = p;
		if (e.key < p->key)
			p = p->lchild;
		else
			p = p->rchild;
	}
	z->parent = temp;
	if (temp == nil)
		root = z;
	else if (z->key < temp->key)
		temp->lchild = z;
	else
		temp->rchild = z;
	++treeSize;
}
//**************************************************************************
BinarySearchTree::
~BinarySearchTree() {
	clearUp(root);
	delete nil;
};
//**************************************************************************
void BinarySearchTree::
set(ElementType *r) {
	r->parent = nil;
	r->lchild = nil;
	r->rchild = nil;
}
//*************************************************************************
void BinarySearchTree::
deleteKey(KeyType k) {
	ElementType *p = search(k);
	if (p == nil) {
		std::cout << "element don't exisit" << std::endl
			<< root << std::endl
			<< nil->parent << " " << nil->lchild << " " << nil->rchild << std::endl;
			return;
	}
	deleteElement(p);
}
//**************************************************************************
void BinarySearchTree::
deleteElement(ElementType *r) {
	ElementType *pt = r, *succ;
	static bool flag = true;
	if (pt == nil)
		return;
	if (pt->lchild == nil)
		transplant(pt, pt->rchild);
	else if (pt->rchild == nil)
		transplant(pt, pt->lchild);
	else{
		if (flag == true) {
			succ = minimum(pt->rchild);
			if (succ->parent != pt) {
				transplant(succ, succ->rchild);
				succ->rchild = pt->rchild;
				succ->rchild->parent = succ;
			}
			transplant(pt, succ);
			succ->lchild = pt->lchild;
			succ->lchild->parent = succ;
			flag = false;
		}
	else{
			succ = maximum(pt->lchild);
			if (succ->parent != pt) {
				transplant(succ, succ->lchild);
				succ->lchild = pt->lchild;
				succ->lchild->parent = succ;
			}
			transplant(pt, succ);
			succ->rchild = pt->rchild;
			succ->rchild->parent = succ;
			flag = true;
		}

	}
	delete pt;
	--treeSize;
}
//**************************************************************************
void BinarySearchTree::
transplant(ElementType *r1, ElementType *r2) {
	if (r1->parent == nil)
		root = r2;
	else if (r1 == r1->parent->lchild)
		r1->parent->lchild = r2;
	else
		r1->parent->rchild = r2;
	//if (r2 != nil)
	r2->parent = r1->parent;
}

BinarySearchTree::ElementType* BinarySearchTree::
minimum(ElementType *r) const {
	if (r == nil)
		return nil;
	while (r->lchild != nil)
		r = r->lchild;
	return r;
}
//****************************************************************************
BinarySearchTree::ElementType* BinarySearchTree::
maximum(ElementType *r) const {
	if (r == nil)
		return nil;
	while (r->rchild != nil)
		r = r->rchild;
	return r;
}
//***************************************************************************
BinarySearchTree::ElementType* BinarySearchTree::
search(KeyType k) const {
	ElementType *pr = root;
	while (pr != nil && pr->key != k) {
		if (k < pr->key)
			pr = pr->lchild;
		else
			pr = pr->rchild;
	}
	return pr;
}
//****************************************************************************
BinarySearchTree::ElementType* BinarySearchTree::
successor(ElementType *r) const {
	if (r == nil)
		return r;
	if (r->rchild != nil)
		return minimum(r->rchild);
	ElementType *temp = r->parent;
	while (temp != nil && r == temp->rchild) {
		r = temp;
		temp = temp->parent;
	}
	return temp;
}
//****************************************************************************
BinarySearchTree::ElementType* BinarySearchTree::
predecessor(ElementType *r) const {
	if (r == nil)
		return r;
	if (r->lchild != nil)
		return maximum(r->lchild);
	ElementType *temp = r->parent;
	while (temp != nil && r == temp->lchild) {
		r = temp;
		temp = temp->parent;
	}
	return temp;
}
//*****************************************************************************
void BinarySearchTree::
clearUp(ElementType *r) {
	if (r != nil) {
		BinarySearchTree::clearUp(r->lchild);
		BinarySearchTree::clearUp(r->rchild);
		print(std::cout, r);                             //打印清除过程，可删除
		delete r;
	}
}