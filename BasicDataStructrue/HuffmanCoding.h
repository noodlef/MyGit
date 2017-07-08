#pragma once
#ifndef HUFFMAN_CODEING_H
#define HUFFMAN_CODEING_H
#include"PriorityQueue.h"
#include<string>
#include<Vector>
template<typename T1>
void huffmanCoding(T1 c[], float freq[], size_t N, std::vector<std::string> &container)
{
	if (N <= 1) {
		container.push_back("0");
		return;
	}
	struct Node {
		float frequence = 0.0;
		T1 c;
		std::string huffmanCode;
	};
	vector<Node> H;
	for (int i = 0; i != N; ++i) {
		Node e;
		e.c = c[i];
		e.frequence = freq[i];
		H.push_back(e);
	}
	PriorityQueue<float, std::vector<Node*>, 'm'> q;                           //关键字小优先级高
	for (int i = 0; i != N; ++i) {
		std::vector<Node*> v{ &H[i] };
		q.add(H[i].frequence, v);
	}
	while (q.Size() > 1) {
		std::vector<Node*> v1, v2, v3;
		float sumFrq = q.maximum().key;
		v1 = q.extractMax().element;
		sumFrq += q.maximum().key;
		v2 = q.extractMax().element;
		for (int i = 0; i != v1.size(); ++i) {
			Node *N = v1[i];
			N->huffmanCode.insert(0,"0");
			v3.push_back(N);
		}
		for (int i = 0; i != v2.size(); ++i) {
			Node *N = v2[i];
			N->huffmanCode.insert(0,"1");
			v3.push_back(N);
		}
		q.add(sumFrq, v3);
	}
	for (int i = 0; i != N; ++i) {
		container.push_back(H[i].huffmanCode);
	}

}
#endif