#include"RedBlackTree.h"
using namespace Tree;
//********************************************
std::ostream &RedBlackTree::
print(std::ostream &os, const ElementType *e) const {
	os << "key " << e->key << " is ";
	if (e->parent != nil) {
		if (e->parent->lchild == e)
			os << " " << "left child of key " << e->parent->key
			<< "(color = " << e->color << ")"
			<< std::endl;
		else
			os << " " << "right child of key " << e->parent->key
			<< "(color = " << e->color << ")"
			<< std::endl;
	}
	else
		os << "root"
		<< "(color = " << e->color << ")"
		<< std::endl;
	return os;
}
//*********************************************
void RedBlackTree::
RB_tree_fixUp(ElementType *r) {
	ElementType *temp;
	while (r->parent->color == RED) {
		if (r->parent == r->parent->parent->lchild) {
			temp = r->parent->parent->rchild;
			if (temp->color == RED) {
				r->parent->color = BLACK;
				temp->color = BLACK;
				r->parent->parent->color = RED;
				r = r->parent->parent;
			}
			else {
				if (r == r->parent->rchild) {
					r = r->parent;
					leftRotate(r);
				}
				r->parent->color = BLACK;
				r->parent->parent->color = RED;
				rightRotate(r->parent->parent);
			}
		}
		else {
			temp = r->parent->parent->lchild;
			if (temp->color == RED) {
				r->parent->color = BLACK;
				temp->color = BLACK;
				r->parent->parent->color = RED;
				r = r->parent->parent;
			}
			else {
				if (r == r->parent->lchild) {
					r = r->parent;
					rightRotate(r);
				}
				r->parent->color = BLACK;
				r->parent->parent->color = RED;
				leftRotate(r->parent->parent);
			}
		}
	}
	root->color = BLACK;
}
//*********************************************
void RedBlackTree::
deleteElement(ElementType *r) {
	ElementType tempNil = *nil;                      // 保存nil的值，下面操作可能改变他
	ElementType *y = r, *x;
	Color y_original_color = y->color;
	if (r == nil)
		return;
	if (r->lchild == nil) {
		x = r->rchild;
		transplant(r, r->rchild);
	}
	else if (r->rchild == nil) {
		x = r->lchild;
		transplant(r, r->lchild);
	}
	else {
		y = minimum(r->rchild);
		y_original_color = y->color;
		x = y->rchild;
		if (y->parent == r)
			x->parent = y;
		else {
			transplant(y, y->rchild);
			y->rchild = r->rchild;
			y->rchild->parent = y;
		}
		transplant(r, y);
		y->lchild = r->lchild;
		y->lchild->parent = y;
		y->color = r->color;
	}
	if (y_original_color == BLACK)
		RB_delete_fixUp(x);
	*nil = tempNil;                //恢复nil的值
	delete r;
	--treeSize;
}
//********************************************
void RedBlackTree::
leftRotate(ElementType *r) {
	ElementType *temp = r->rchild;
	r->rchild = temp->lchild;
	if (temp->lchild != nil)
		temp->lchild->parent = r;
	temp->parent = r->parent;
	if (r->parent == nil)
		root = temp;
	else if (r == r->parent->lchild)
		r->parent->lchild = temp;
	else
		r->parent->rchild = temp;
	temp->lchild = r;
	r->parent = temp;
}
//**********************************************
void RedBlackTree::
rightRotate(ElementType *r) {
	ElementType *temp = r->lchild;
	r->lchild = temp->rchild;
	if (temp->rchild != nil)
		temp->rchild->parent = r;
	temp->parent = r->parent;
	if (r->parent == nil)
		root = temp;
	else if (r == r->parent->lchild)
		r->parent->lchild = temp;
	else
		r->parent->rchild = temp;
	temp->rchild = r;
	r->parent = temp;
}
//**********************************************
void RedBlackTree::
insert(const ElementType &e) {
	ElementType *z = new ElementType(e.key, e.p);
	ElementType *p = root, *temp = nil;
	set(z);
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
	z->color = RED;
	RB_tree_fixUp(z);
}
//**********************************************
void RedBlackTree::
RB_delete_fixUp(ElementType *r) {
	ElementType *w;
	while (r != root && r->color == BLACK) {
		if (r == r->parent->lchild) {
			w = r->parent->rchild;
			if (w->color == RED) {
				w->color = BLACK;
				r->parent->color = RED;
				leftRotate(r->parent);
				w = r->parent->rchild;
			}
			if (w->lchild->color == BLACK && w->rchild->color == BLACK) {
				w->color = RED;
				r = r->parent;
			}
			else {
				if (w->rchild->color == BLACK) {
					w->lchild->color = BLACK;
					w->color = RED;
					rightRotate(w);
					w = r->parent->rchild;
				}
				w->color = r->parent->color;
				r->parent->color = BLACK;
				w->rchild->color = BLACK;
				leftRotate(r->parent);
				break;
			}
		}
		else {
			w = r->parent->lchild;
			if (w->color == RED) {
				w->color = BLACK;
				r->parent->color = RED;
				rightRotate(r->parent);
				w = r->parent->lchild;
			}
			if (w->lchild->color == BLACK && w->rchild->color == BLACK) {
				w->color = RED;
				r = r->parent;
			}
			else {
				if (w->lchild->color == BLACK) {
					w->rchild->color = BLACK;
					w->color = RED;
					leftRotate(w);
					w = r->parent->lchild;
				}
				w->color = r->parent->color;
				r->parent->color = BLACK;
				w->lchild->color = BLACK;
				rightRotate(r->parent);
				break;
			}
		}
	}
	r->color = BLACK;
}