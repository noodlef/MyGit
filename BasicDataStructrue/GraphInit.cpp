// 从文件中读有向图G(V , E)的函数
// 文件的每行的第一个数据表示当前的顶点   S 
// 其余数据表示与顶点 S 相连的其他所有顶点集合， 其每个数据代表有向边 : S --> D
#include<fstream>
#include<sstream>
#include<string>
#include"LinkList.h"
struct Edge {                                                                     // 有向图边的结构
	size_t tail;
	int wight;
};
struct Vertex{                                                                    // 有向图顶点的结构
	size_t v;
};
const size_t vertexNum = 20;                                                      // 有向图顶点的个数
templa::LinkList<Edge> list[vertexNum];
Vertex vertex[vertexNum];
//**************************************************************************
static void VertexInit(size_t i) {                                                // 顶点初始化
	vertex[i].v = i;
}
static void EdgeInit(std::ifstream &file, templa::LinkList<Edge> *list) {         // 边初始化
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
	EdgeInit(file,list);
	
}