#pragma once
#ifndef RED_BLACK_TREE
#define RED_BLACK_TREE
#include"BinarySearchTree_base.h"
namespace Tree {
	class RedBlackTree : public BinarySearchTree {
		std::ostream& print(std::ostream &os, const ElementType *e) const;
		void insert(const ElementType &e);
		void deleteElement(ElementType *r);
		void leftRotate(ElementType *r);
		void rightRotate(ElementType *r);
		void RB_tree_fixUp(ElementType *r);
		void RB_delete_fixUp(ElementType *r);

	};
}
#endif