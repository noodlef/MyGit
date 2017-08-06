#include<fstream>
#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
#include"stack.h"
#include"LinkList.h"
#define INF 65535
#define NIL -1
// 有向图边的结构
struct Edge {                                                                    
	size_t tail;
	int wight;
};
// 有向图顶点的结构
struct Vertex {                                                                 
	size_t parent;
	int distance;
};
// 有向图顶点的个数
const size_t vertexNum = 4;                                                    
templa::LinkList<Edge> list[vertexNum];
Vertex vertex[vertexNum];
//**************************************************************************
// 顶点初始化
static void VertexInit(size_t i) {                                                
	vertex[i].parent = NIL;
	vertex[i].distance = INF;
}
// 边初始化
static void EdgeInit(std::ifstream &file, templa::LinkList<Edge> *list) {         
	Edge e;
	std::string line1, line2;
	size_t index = 0;
	while (getline(file, line1) && getline(file, line2)) {
		std::istringstream vertex(line1), wight(line2);
		while (vertex >> e.tail && wight >> e.wight)
			list[index].push_back(e);
		++index;
	}
}
void GraphInit(std::ifstream &file) {
	for (size_t i = 0; i != vertexNum; ++i)
		VertexInit(i);
	EdgeInit(file, list);

}
//*****************************************************************************
// Bellman-Ford 算法 计算带权重有向图 G(V,E)给定源点 s 到 其它顶点 v 的最短路径
// 该算法对边的权重为负值情况也能工作
bool BellmanFord(std::ifstream &file, size_t sourceVertex) {
	GraphInit(file);
	vertex[sourceVertex].distance = 0;
	for (size_t i = 1; i != vertexNum; i++) {
		// 对图中的每条边进行松弛
		for (size_t j = 0; j != vertexNum; j++) {
			size_t M = j, counter = list[M].size();
			for (size_t k = 0; k != counter; k++) {
				size_t V = list[M][k].tail;
				int wight = list[M][k].wight;
				if (vertex[V].distance - vertex[M].distance > wight) {
					vertex[V].distance = vertex[M].distance + wight;
					vertex[V].parent = M;
				}
			}
		}
	}
	// 检测图中是否有源节点 s 可到达的权重为负值的环路
	for (size_t j = 0; j != vertexNum; j++) {
		size_t M = j, counter = list[M].size();
		for (size_t k = 0; k != counter; k++) {
			size_t V = list[M][k].tail;
			int wight = list[M][k].wight;
			if (vertex[V].distance - vertex[M].distance > wight)
				return false;
		}
	}
	return true;
}
//***************************************************************************
// Dijkstra算法解决的是带权重的有向图上单源最短路径问题
// 该算法要求边的权重为正值
#include"PriorityQueue.h"
void Dijkstra(std::ifstream &file, size_t sourceVertex) {
	PriorityQueue<int, size_t,'m'> Q;
	Data <int, size_t> d;
	GraphInit(file);
	vertex[sourceVertex].distance = 0;
	for (size_t i = 0; i != vertexNum; i++) {
		d = { vertex[i].distance, i };
		Q.add(d);
	}
	while (!Q.empty()) {
		d = Q.extractMin();
		size_t M = d.element, counter = list[M].size();
		// 对与顶点 M 相连的边进行松弛
		for (size_t k = 0; k != counter; k++) {
			size_t V = list[M][k].tail;
			int wight = list[M][k].wight;
			if (vertex[V].distance - vertex[M].distance > wight) {
				vertex[V].distance = vertex[M].distance + wight;
				vertex[V].parent = M;
				Q.setKey(V, vertex[V].distance);
			}
		}
	}
}
//***************************************************************************
// 打印出路径
void PrintPath(size_t sourceVertex) {
	std::cout << std::left 
		      << "sourceVertex : " << sourceVertex
		      << "       "
		      << "vertexNum : " << vertexNum << std::endl;
	for (size_t i = 0; i != vertexNum; ++i) {
		// 求出每个顶点的最短路径
		size_t  dest = i ,v = dest;
		templa::Stack<size_t> path;
		path.push(dest);
		while ((v = vertex[v].parent) != NIL) 
			path.push(v);
		std::cout <<"path distance : " << vertex[dest].distance << std::endl;
		if ((v = path.pop() )== sourceVertex) {
			std::cout << v;
			while (!path.stackEmpty()) {
				v = path.pop();
				std::cout << "-->" << v;
			}
			std::cout << std::endl;
		}
		else 
			std::cout << "no path" << std::endl;
		std::cout << std::endl;
	}
}
//*****************************************************************************
int main() {
	//std::ifstream file("bellman.txt");
	std::ifstream file("Dijkstra.txt");
	size_t sourceVertex = 0;
	//BellmanFord(file, sourceVertex);
	Dijkstra(file, sourceVertex);
	PrintPath(sourceVertex);
	system("pause");
	return 0;
}