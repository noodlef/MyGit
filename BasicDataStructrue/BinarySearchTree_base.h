#pragma once
#ifndef BINARY_SEARCH_TREE_BASE_H
#define BINARY_SEARCH_TREE_BASE_H
#include<iostream>
#include<string>
namespace Tree {
	struct Data {
		typedef int KeyType;                              // 关键字的类型
		typedef std::string SatalliteData;                // 包含的卫星数据
		KeyType key;                                                            //一定要含有默认构造函数
		SatalliteData p;                                                        //一定要含有默认构造函数
	};
	class BinarySearchTree {
	public:
		friend std::ostream &print(std::ostream &os, const BinarySearchTree &tree); //打印整棵树
		typedef Data::KeyType KeyType;
		typedef Data::SatalliteData SatalliteData;
		void add(const Data &dat);                                                 //插入元素
		Data searchKey(KeyType k) const;                                           //用关键字搜索
		Data maximumKey() const;                                                   //返回最大关键字元素
		Data minimumKey() const;
		Data successorKey(KeyType k) const;                                        //后继
		Data predecessorKey(KeyType k) const;                                      //前驱
		void deleteKey(KeyType k);                                                 //根据关键字删除
		size_t size() const { return treeSize; }                                   //树的大小
		BinarySearchTree();                                                        //默认构造函数
		BinarySearchTree(const BinarySearchTree &tree) = delete; //禁止拷贝构造
		BinarySearchTree& operator=(const BinarySearchTree &tree) = delete;//禁止拷贝赋值
		virtual ~BinarySearchTree();                                              //析构函数                            (虚)
	protected:
		enum Color { RED, BLACK, YELLOW };                          // 红黑树
		struct ElementType {                                        // 存贮在树中的元素类型
			ElementType *lchild;
			ElementType *rchild;
			ElementType *parent;
			KeyType key;
			SatalliteData p;
			ElementType() = default;
			Color color = YELLOW;                                        // 红黑树属性
			ElementType(KeyType k, SatalliteData s, Color col = YELLOW); // 构造函数
		};
		virtual std::ostream &print(std::ostream &os, const ElementType *e) const;// 打印信息                           (虚)
		void inorderTreeWalk(const ElementType *p) const;                         // 中序遍历
		virtual void insert(const ElementType &e);                                // 插入元素                           (虚)
		ElementType *minimum(ElementType *r) const;                               // 最小值
		ElementType *maximum(ElementType *r) const;                               // 最大值
		ElementType *successor(ElementType *r) const;                             // 前驱
		ElementType *predecessor(ElementType *r) const;                           // 后继
		ElementType *search(KeyType k) const;                                     // 搜索
		void transplant(ElementType *r1, ElementType *r2);                        // 移植
		virtual void deleteElement(ElementType *r);                               // 删除树中元素r                      (虚) 
		void clearUp(ElementType *r);                                             // 清除以r为根的子树,释放空间
		void set(ElementType *r);
		//private:
		size_t treeSize;                               //树的大小
		ElementType *root;                             //树根
		ElementType *nil;                              //标兵
	};
	std::ostream &print(std::ostream &os, const BinarySearchTree &tree);
}
#endif