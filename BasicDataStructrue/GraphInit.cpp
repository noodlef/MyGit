// ���ļ��ж�����ͼG(V , E)�ĺ���
// �ļ���ÿ�еĵ�һ�����ݱ�ʾ��ǰ�Ķ���   S 
// �������ݱ�ʾ�붥�� S �������������ж��㼯�ϣ� ��ÿ�����ݴ�������� : S --> D
#include<fstream>
#include<sstream>
#include<string>
#include"LinkList.h"
struct Edge {                                                                     // ����ͼ�ߵĽṹ
	size_t tail;
	int wight;
};
struct Vertex{                                                                    // ����ͼ����Ľṹ
	size_t v;
};
const size_t vertexNum = 20;                                                      // ����ͼ����ĸ���
templa::LinkList<Edge> list[vertexNum];
Vertex vertex[vertexNum];
//**************************************************************************
static void VertexInit(size_t i) {                                                // �����ʼ��
	vertex[i].v = i;
}
static void EdgeInit(std::ifstream &file, templa::LinkList<Edge> *list) {         // �߳�ʼ��
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