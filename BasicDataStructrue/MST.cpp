// 最小生成树算法
#include"LinkList.h"
#include"PriorityQueue.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using std::string;
const size_t INF = 65535;
#define NIL 65535
const size_t vertexNum = 9;
struct Vertex {
	size_t v;
	size_t parent;
	int key;
};
struct Edge {
	size_t tail;
	int w;
};
templa::LinkList<Edge> list[vertexNum];
Vertex node[vertexNum];
bool vis[vertexNum];
//********************************************************************
void MST_Init() {
	Vertex *beg = node;
	for (size_t i = 0; i != vertexNum; ++i) {
		beg->key = INF;
		beg->parent = NIL;
		beg->v = i;
		++beg;
	}
	Edge e;
	string line1,line2;
	size_t index = 0;
	std::ifstream file("data.txt");
	while (getline(file, line1) && getline(file, line2)) {
		std::istringstream vertex(line1), wight(line2);
		while (vertex >> e.tail && wight >> e.w)
			list[index].push_back(e);
		++index;
	}
}
//********************************************************************
void MST_Prim() {
	Vertex *beg = node;
	MST_Init();
	beg->key = 0;                                    // 设定搜索的起点
	PriorityQueue<int, Vertex*, 'm'> q;
	for (size_t i = 0; i != vertexNum; ++i) {
		q.add(beg->key, beg);
		vis[i] = true;
		++beg;
	}
	while (!q.empty()) {
		Vertex *u = q.extractMin().element;
		size_t vertex = u->v;
		vis[vertex] = false;
		for (size_t i = 0; i != list[vertex].size(); ++i) {
			Edge e = list[vertex][i];
			size_t t = e.tail;
			if (vis[t] == true && e.w < node[t].key) {
				node[t].parent = vertex;
				node[t].key = e.w;
				q.setKey(node + t, e.w);
			}
		}
	}	
}
void main() {
	MST_Prim();
	for (int i = 0; i != vertexNum; ++i) {
		if (node[i].parent != NIL) {
			std::cout << node[i].v << "-->" 
				      << node[i].parent << std::endl;
		}
	}
	system("pause");
 }