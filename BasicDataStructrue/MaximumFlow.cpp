#include<fstream>
#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
//下面是自己编写的数据结构
#include"Queue.h"
#include"LinkList.h"
#define INF 65535
#define NIL -1
enum Color { WHITE, BLACK, GREY};
// 有向图边的结构
struct Edge {
	size_t tail;
	int Mflow;
	int Uflow;
};
// 有向图顶点的结构
struct Vertex {
	size_t parent;
	Color color;
};
// 有向图顶点的个数
const size_t vertexNum = 6;
// 邻接表表示有向图 G(V,E)
templa::LinkList<Edge> Graph[vertexNum];
// 有向图 G(V,E)对应的残存图 G_f(V,E)
templa::LinkList<Edge> ResidualGraph[vertexNum];
Vertex vertex[vertexNum];
//**************************************************************************
//struct list_head;
struct list_head {
	list_head *prece;
	list_head *succ;
};
struct Fox {
	Edge e;
	list_head list;
};
//struct list_head {
//	list_head *prece;
//	list_head *succ;
//};
//#define container_of(ptr, type, member)( \

//**************************************************************************
// 顶点初始化, 用于 BFS 算法
static void VertexInit() {
	for (size_t i = 0; i != vertexNum; ++i) {
		vertex[i].parent = NIL;
		vertex[i].color = WHITE;
	}
}
// 有向图G(V, E) 和 残存图 G_f(V,E)初始化
static void GraphInit(std::ifstream &file) {
	Edge e;
	std::string line1, line2;
	size_t index = 0;
	while (getline(file, line1) && getline(file, line2)) {
		std::istringstream vertex(line1), flow(line2);
		while (vertex >> e.tail && flow >> e.Mflow) {
			e.Uflow = 0;
			Graph[index].push_back(e);
			ResidualGraph[index].push_back(e);
		}
		++index;
	}
}
//****************************************************************************
static size_t GetEdge(size_t s, size_t t, templa::LinkList<Edge> *Graph) {
	size_t counter = Graph[s].size();
	for (size_t i = 0; i != counter; ++i) {
		if (Graph[s][i].tail == t)
			return i;
	}
	return 0;
}
static int GetPath(Queue<size_t> &path, templa::LinkList<Edge> *Graph) {
	int flow = INF,f;
	size_t  j = path[0], i,index;
	while ((i = vertex[j].parent) != NIL) {
		path.push_front(i);
		index = GetEdge(i, j, Graph);
		if ((f = Graph[i][index].Mflow) < flow)
			flow = f;
		j = i;
	}
	return flow;
}
//****************************************************************************
//  ----------------------广度优先搜索算法————————————
//
// path 用于存放路径，初始时其中放有 sourceVertex, destVertex
// 如果找到从 sourceVertex ---> destVertex 的路径则函数返回该
// 路径的最大流 flow,否则函数返回 0，且路径存放在 path 中
static int BFS(Queue<size_t> &path, templa::LinkList<Edge> *Graph) {
	size_t sourceVertex = path.pop_front(), destVertex = path[0];
	Queue<size_t> q;
	// 对各个顶点 V 初始化
	VertexInit();
	vertex[sourceVertex].color = GREY;
	q.push_back(sourceVertex);
	while (!q.empty()) {
		size_t u = q.pop_front();
		size_t counter = Graph[u].size();
		for (size_t i = 0; i != counter; ++i) {
			size_t temp = Graph[u][i].tail;
			if (vertex[temp].color == WHITE) 
			{
				vertex[temp].color = GREY;
				vertex[temp].parent = u;
				//已经找到路径了，下面把路径存在 path 中
				if (temp == destVertex)
					return GetPath(path, Graph);
				q.push_back(temp);
			}
		}
		vertex[u].color = BLACK;
	}
	return 0;
}
//****************************************************************************
//  ----------------------最大流 EdmondsKarp 算法————————————
int EdmondsKarp(std::ifstream &file, size_t sourceVertex , size_t destVertex ) {
	int flow = 0, ret = 0;
	Queue<size_t> path;
	path.push_back(sourceVertex);
	path.push_back(destVertex);
	GraphInit(file);
	while (flow = BFS(path, ResidualGraph)) {
		for (int i = 0; i != path.Size(); ++i) {
			std::cout << path[i] << " " ;
		}
		std::cout << "flow = " << flow << std::endl;
		size_t s = path.pop_front(),t,index;
			while (!path.empty()) {
				t = path.pop_front();
				index = GetEdge(s, t, ResidualGraph);
				if (ResidualGraph[s][index].Mflow > flow)
					ResidualGraph[s][index].Mflow -= flow;
				else
					ResidualGraph[s].pop(index);
				if (index = GetEdge(t, s, ResidualGraph))
					ResidualGraph[t][index].Mflow += flow;
			    else
					ResidualGraph[t].push_back({ s,flow,0 });
				s = t;
			}
			ret += flow;
			path.push_back(sourceVertex);
			path.push_back(destVertex);
	}
	return ret;
}
//****************************************************************************
//int main() {
//	std::ifstream file("MaximumFlow.txt");
//	size_t sourceVertex = 0, destVertex = 5;
//	int a = EdmondsKarp(file, sourceVertex, destVertex);
//	/*Queue<size_t> path;
//	path.push_back(sourceVertex);
//	path.push_back(destVertex);
//	GraphInit(file);
//	if (BFS(path, Graph))
//		while (!path.empty())
//			std::cout << path.pop_front() << "-->";
//	*/
//	system("pause");
//}