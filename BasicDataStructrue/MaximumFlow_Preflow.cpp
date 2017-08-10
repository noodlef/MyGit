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
struct Edge {
	// 边还能通过的最大流量
	int Mflow;
	// 边已经通过的总流量
	int flow;
};
const size_t vertexNum = 6;
int Graph[vertexNum][vertexNum];
static Edge ResidualGraph[vertexNum][vertexNum];
// 流溢出节点vertex的集合
static templa::LinkList<size_t> ExceVertex;
// 超额流存放在 ResidualGraph[v][v].Mflow 中
// 顶点 v 的高度 h 放在 ResidualGraph[v][v].flow
#define Get_E_Flow(v)  ResidualGraph[v][v].Mflow 
#define Get_hight(v)   ResidualGraph[v][v].flow
// 判断一条边是不是原始边
static inline bool IsGraph(size_t i, size_t j) {
	if (Graph[i][j] == 0)
		return false;
	return true;
}
// 判断残存图中一条边是否存在
static inline bool present(size_t i, size_t j) {
	if (ResidualGraph[i][j].Mflow == 0)
		return false;
	return true;
}
// 修改顶点 vertex 的超额流量
static inline void ExcessFlow(size_t v, int increment) {
	ResidualGraph[v][v].Mflow += increment;
}
// 修改顶点 vertex 的高度 h
static inline void hight(size_t v, int increment) {
	ResidualGraph[v][v].flow += increment;
}
// 有向图G(V, E) 和 残存图 G_f(V,E)初始化
static void GraphInit(std::ifstream &file) {
	int Mflow = 0;
	std::string line1, line2;
	size_t row = 0, col = 0;
	for (size_t i = 0; i != vertexNum; ++i) 
		for (size_t j = 0; j != vertexNum; ++j) 
			Graph[i][j] = 0;
	while (getline(file, line1) && getline(file, line2)) {
		std::istringstream vertex(line1), flow(line2);
		while (vertex >> col && flow >> Mflow) 
			Graph[row][col] = Mflow;
		++row;
	}
}
// 推送预流操作
static void push(size_t i, size_t j) {
	int flow = ResidualGraph[i][j].Mflow;
	if (flow > Get_E_Flow(i))
		flow = Get_E_Flow(i);
	if (IsGraph(i, j))
		ResidualGraph[i][j].flow += flow;
	ResidualGraph[i][j].Mflow -= flow;
	ResidualGraph[j][i].Mflow += flow;
	ExcessFlow(i, -flow);
	ExcessFlow(j, flow);
}
// 重贴标签操作
static size_t relabel(size_t v) {
	size_t ret = 0;
	int h = INF, temp = Get_hight(v);
	for(size_t j = 0; j != vertexNum; ++j)
		// j 与 v 相连
		if (j != v && present(v, j)) {
			if (h > Get_hight(j)) {
				h = Get_hight(j);
				ret = j;
			}
		}
	hight(v, 1 + h - temp);
	return ret;
}
// 预流初始化
static void InitPreflow(size_t s, int (*Graph)[vertexNum]) {
	Edge e = { 0, 0 };
	for(size_t i = 0; i != vertexNum; ++i)
		for (size_t j = 0; j != vertexNum; ++j) {
			if (i != j)
				ResidualGraph[i][j] = { Graph[i][j], 0 };
			else
	// ResidualGraph[i][i]中存放着每个vertex的超额流(E_Flow)和高度(h)
				ResidualGraph[i][i] = { 0, 0 };
		}
	Get_hight(s) = vertexNum;
	for (size_t i = 0; i != vertexNum; ++i) {
		if (i != s && present(s, i)) {
			int Mflow = ResidualGraph[s][i].Mflow;
			ResidualGraph[s][i].flow = Mflow;
			// 删除边 s --> i
			ResidualGraph[s][i].Mflow = 0;
			// 增加反方向边 i --> s
			ResidualGraph[i][s] = { Mflow,0 };
			Get_E_Flow(i) = Mflow;
			// 把顶点 i 加入溢出顶点集合
			ExceVertex.push_back(i);
			Get_E_Flow(s) -= Mflow;
		}
	}
}
// 通用推送重贴标算法
int GenericPushRelabel(int(*Graph)[vertexNum], size_t sourcVertex, size_t destVertex) {
	InitPreflow(sourcVertex, Graph);
	while (!ExceVertex.empty()) {
		size_t vertex = ExceVertex.at(0), i;
		for (i = 0; i != vertexNum; ++i) {
			if (i != vertex && present(vertex, i)) 
				if ((Get_hight(i) + 1) == Get_hight(vertex)) {
					int iflow = Get_E_Flow(i);
					push(vertex, i);
					if (Get_E_Flow(vertex) == 0)
						ExceVertex.pop_front();
					if (iflow == 0 && i != destVertex)
						ExceVertex.push_front(i);
					break;
				}
		}
		if (i == vertexNum) {
			size_t index = relabel(vertex);
			int iflow = Get_E_Flow(index);
			push(vertex, index);
			if (Get_E_Flow(vertex) == 0)
				ExceVertex.pop_front();
			if (iflow == 0 && index != destVertex)
				ExceVertex.push_front(index);
		}
	}
	return Get_E_Flow(destVertex);
}
int main() {
	std::ifstream file("MaximumFlow.txt");
	GraphInit(file);
	size_t sourcVertex = 0, destVertex = 5;
	int a = GenericPushRelabel(Graph, sourcVertex, destVertex);
	system("pause");
	return 0;
}