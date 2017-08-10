#include<fstream>
#include<iostream>
#include<iomanip>
#include<sstream>
#include<string>
//�������Լ���д�����ݽṹ
#include"Queue.h"
#include"LinkList.h"
#define INF 65535
#define NIL -1
struct Edge {
	// �߻���ͨ�����������
	int Mflow;
	// ���Ѿ�ͨ����������
	int flow;
};
const size_t vertexNum = 6;
int Graph[vertexNum][vertexNum];
static Edge ResidualGraph[vertexNum][vertexNum];
// ������ڵ�vertex�ļ���
static templa::LinkList<size_t> ExceVertex;
// ����������� ResidualGraph[v][v].Mflow ��
// ���� v �ĸ߶� h ���� ResidualGraph[v][v].flow
#define Get_E_Flow(v)  ResidualGraph[v][v].Mflow 
#define Get_hight(v)   ResidualGraph[v][v].flow
// �ж�һ�����ǲ���ԭʼ��
static inline bool IsGraph(size_t i, size_t j) {
	if (Graph[i][j] == 0)
		return false;
	return true;
}
// �жϲд�ͼ��һ�����Ƿ����
static inline bool present(size_t i, size_t j) {
	if (ResidualGraph[i][j].Mflow == 0)
		return false;
	return true;
}
// �޸Ķ��� vertex �ĳ�������
static inline void ExcessFlow(size_t v, int increment) {
	ResidualGraph[v][v].Mflow += increment;
}
// �޸Ķ��� vertex �ĸ߶� h
static inline void hight(size_t v, int increment) {
	ResidualGraph[v][v].flow += increment;
}
// ����ͼG(V, E) �� �д�ͼ G_f(V,E)��ʼ��
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
// ����Ԥ������
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
// ������ǩ����
static size_t relabel(size_t v) {
	size_t ret = 0;
	int h = INF, temp = Get_hight(v);
	for(size_t j = 0; j != vertexNum; ++j)
		// j �� v ����
		if (j != v && present(v, j)) {
			if (h > Get_hight(j)) {
				h = Get_hight(j);
				ret = j;
			}
		}
	hight(v, 1 + h - temp);
	return ret;
}
// Ԥ����ʼ��
static void InitPreflow(size_t s, int (*Graph)[vertexNum]) {
	Edge e = { 0, 0 };
	for(size_t i = 0; i != vertexNum; ++i)
		for (size_t j = 0; j != vertexNum; ++j) {
			if (i != j)
				ResidualGraph[i][j] = { Graph[i][j], 0 };
			else
	// ResidualGraph[i][i]�д����ÿ��vertex�ĳ�����(E_Flow)�͸߶�(h)
				ResidualGraph[i][i] = { 0, 0 };
		}
	Get_hight(s) = vertexNum;
	for (size_t i = 0; i != vertexNum; ++i) {
		if (i != s && present(s, i)) {
			int Mflow = ResidualGraph[s][i].Mflow;
			ResidualGraph[s][i].flow = Mflow;
			// ɾ���� s --> i
			ResidualGraph[s][i].Mflow = 0;
			// ���ӷ������ i --> s
			ResidualGraph[i][s] = { Mflow,0 };
			Get_E_Flow(i) = Mflow;
			// �Ѷ��� i ����������㼯��
			ExceVertex.push_back(i);
			Get_E_Flow(s) -= Mflow;
		}
	}
}
// ͨ�������������㷨
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