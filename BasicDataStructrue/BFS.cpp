//广度优先搜索算法
#include"LinkList.h"
#include<iomanip>
#include<iostream>
#include<vector>
#include<string>
#include<iterator>
#include"stack.h"
#include"Queue.h"
#include"Sort.h"
//*********************************************************************
enum Color{WHITE, BLACK, GREY, INFINITE = 65535, NIL = -1};
struct Vertex {
	size_t v;                                              // 节点编号
	Color color = WHITE;
	int distance = INFINITE;
	size_t parent = NIL;
	size_t sTime = 0, fTime = 0;
};
struct Edge{
	typedef size_t property;
	size_t tail ;
	property pro ;                                         //  0,1,2,3分别表示深度优先搜索的 树边，前向边， 后向边， 横向边
};
const size_t vertexNum = 14;                               // 图的顶点个数
Vertex node[vertexNum];
templa::LinkList<Edge> list[vertexNum];                   // 邻接表
//********************************************************************
void init(templa::LinkList<Edge> list[], size_t vertexNum) {
	for (int i = 0; i != vertexNum; ++i) {
		node[i].v = i;
	}
	//list[0].insert({ {1, INFINITE },{ 3 ,INFINITE } });       // 初始化每条边的属性值为 :INFINITE
	//list[1].insert({ { 4, INFINITE } });
	//list[2].insert({ { 4, INFINITE },{ 5 ,INFINITE } });
	////list[3].insert({ { 1, INFINITE } });
	//list[4].insert({ { 3 ,INFINITE } });
	////list[5].insert({ { 5, INFINITE } });
	list[0].insert({ { 4, INFINITE },{ 5, INFINITE },{ 11, INFINITE } });
	list[1].insert({ { 2, INFINITE },{ 4, INFINITE },{ 8, INFINITE } });
	list[2].insert({ { 5, INFINITE },{ 6, INFINITE },{ 9, INFINITE } });
	list[3].insert({ { 2, INFINITE },{ 6, INFINITE },{ 13, INFINITE } });
	list[4].insert({ { 7, INFINITE } });
	list[5].insert({ { 8, INFINITE },{ 12, INFINITE } });
	list[6].insert({ { 5, INFINITE } });
	list[8].insert({ { 7, INFINITE } });
	list[9].insert({ { 10, INFINITE },{ 11, INFINITE } });
	list[10].insert({ { 13, INFINITE } });
	list[12].insert({ { 9, INFINITE }});
}
//********************************************************************
void printBFS(std::ostream &os, Vertex node[], size_t vertexNum, size_t sourceVertex) {
	os << std::left 
	   << std::setw(12) << "vertex"
	   << std::setw(25) << "distance to sourceVertex(" << sourceVertex << ")"
	   <<"         "
	   << std::setw(12) << "parent vertex" << std::endl;
	for (int i = 0; i != vertexNum; ++i) {
		os << std::left
		   << std::setw(12) << node[i].v;  
		if (node[i].parent == NIL) {
			os << std::setw(36) << "INFINITY"
			   << std::setw(12) << "NIL" << std::endl;
		}
		else {
			os << std::setw(36) << node[i].distance
			   << std::setw(12) << node[i].parent << std::endl;
			}
	}
}
//********************************************************************
// 广度优先搜索
void BFS() {
	//templa::LinkList<Edge> list[vertexNum];                    // 邻接链表来表示边
	init(list, vertexNum);
	size_t sourceVertex = 1;
	node[sourceVertex].distance = 0;
	node[sourceVertex].color = GREY;
	Queue<size_t> q;
	q.push_back(sourceVertex);
	while (!q.empty()) {
		size_t u = q.pop_front();
		size_t counter = list[u].size();
		for (size_t i = 0; i != counter; ++i) {
			size_t temp = list[u][i].tail;
			if (node[temp].color == WHITE) {
				node[temp].color = GREY;
				node[temp].distance = node[u].distance + 1;
				node[temp].parent = u;
				q.push_back(temp);
			}
		}
		node[u].color = BLACK;
	}
}
//********************************************************************
void property(templa::LinkList<Edge> list[], size_t vertexNum) {
	for (int i = 0; i != vertexNum; ++i) {
		for (int j = 0; j != list[i].size(); ++j) {
			if (list[i][j].pro == 0)
				continue;
			else {
				size_t vertex = list[i][j].tail;
				if (node[vertex].fTime < node[i].sTime)
					list[i][j].pro = 3;
				else {
					if(node[i].sTime < node[vertex].sTime)
						list[i][j].pro = 1;
					else
						list[i][j].pro = 2;
				}
			}

		}
	}
	/*for (int i = 0; i != vertexNum; ++i) {
		for (int j = 0; j != list[i].size(); ++j) {
			std::cout << i << "  " << list[i][j].tail << "  ";
			if (list[i][j].pro == 0)
				std::cout << "tree edge" << std::endl;
			else if (list[i][j].pro == 1)
				std::cout << "front edge" << std::endl;
			else if (list[i][j].pro == 2)
				std::cout << "back edge" << std::endl;
			else
				std::cout << "cross edge" << std::endl;
		}
	}*/
}
//********************************************************************
// 深度优先搜索———非递归调用方式
void deepFirstSearch() {
	//templa::LinkList<Edge> list[vertexNum];   //邻接表表示边
	init(list, vertexNum);
	templa::Stack<size_t> myStack;
	for (size_t i = 0; i != vertexNum; ++i) {
		size_t vertex = vertexNum - i - 1;                                //              i
		myStack.push(vertex);
	}
	size_t time = 0;
	while (!myStack.stackEmpty()) {
		size_t vertex = myStack.pop();
		if (node[vertex].color == WHITE) {
			++time;
			node[vertex].sTime = time;
			node[vertex].color = GREY;
			myStack.push(vertex);
			size_t counter = list[vertex].size(); 
			size_t index = -1;                                                        // index
			for (size_t i = 0; i != counter; ++i) {
				size_t t = list[vertex][counter - i - 1].tail;                       // i
				if (node[t].color == WHITE) {
					node[t].parent = vertex;
					myStack.push(t);
					index = counter - i - 1;                                         // 记录树边的index
				}
			}
			if(index + 1 != 0)
				list[vertex][index].pro = 0;                                        // 设置边的属性为树边
		}
		else if (node[vertex].color == GREY) {
			++time;
			node[vertex].fTime = time;
			node[vertex].color = BLACK;
		}
	}
	//property(list, vertexNum);                                                 // 求出深度优先搜索过程中条边的属性
}
//********************************************************************
//深度优先搜索————递归调用方式
void DFS_VISIT(size_t index, templa::LinkList<Edge> list[], size_t &time) {
	++time;
	node[index].sTime = time;
	node[index].color = GREY;
	size_t counter = list[index].size();
	for (size_t i = 0; i != counter; ++i) {
		size_t u = list[index][i].tail;
		if (node[u].color == WHITE) {
			node[u].parent = index;
			DFS_VISIT(u, list, time);
			list[index][i].pro = 0;
			//std::cout << "Edge" << index << " " << u << "tree edge" << std::endl;
		}
	}
	node[index].color = BLACK;
	++time;
	node[index].fTime = time;
}

//*********************************************************************
void DFS() {
	templa::LinkList<Edge> list[vertexNum];
	size_t time = 0;
	init(list, vertexNum);
	for (size_t i = 0; i != vertexNum; ++i) {
		if (node[i].color == WHITE) 
			DFS_VISIT(i, list, time);
		}
	//property(list, vertexNum);
}
//********************************************************************
void printDFS(std::ostream &os, Vertex node[], size_t vertexNum) {
	os << std::left
		<< std::setw(12) << "vertex"
		<< std::setw(12) << "sTime"
		<< std::setw(12) << "fTime" << std::endl;
	for (int i = 0; i != vertexNum; ++i) {
		os << std::left
		   << std::setw(12) << node[i].v
		   << std::setw(12) << node[i].sTime
		   << std::setw(12) << node[i].fTime << std::endl;

	}
}
//*********************************************************************
// 搜索给定----------有向无环图
// 从源节点（sourceVetex)到目的节点(destinationVertex)的所有简单路径
// 当某个节点的颜色为--GREY---时表示这个节点是源节点到目的节点的必经节点
// 当某个节点的颜色为--BLACK---时表示这个节点不是源节点到目的节点的必经节点
// 初始时所有节点为--WHITE--表示未知状态
struct Element {
	size_t vertex;
	size_t time;
};
void printPath(Queue<Element> &path, size_t destinationVertex){
	static size_t pathNum = 0;
	std::cout << "path " << pathNum << ": ";
	for (size_t i = 0; i != path.Size(); ++i)                  // 打印路径
		std::cout << path[i].vertex << "--->";
	std::cout << destinationVertex << std::endl;
	++pathNum;
}
void searchPath() {
	//templa::LinkList<Edge> list[vertexNum];
	init(list, vertexNum);
	size_t sourceVertex = 3, destinationVertex = 7, pathNum = 0, time = 0; // pathNum 路径的总个数
	Queue<Element> path;                                                    // 记录路径
	templa::Stack<Element> myStack;
	myStack.push({ sourceVertex, time });
	while (!myStack.stackEmpty()) {
		Element e = myStack.pop();                                          // 记录路径
		size_t t = e.vertex;
		path.push_back(e);                                                  // 记录路径
		size_t counter = list[t].size();
	    bool Flag = true;                                                
		++time;                                                            //  记录路径
		size_t cnt = myStack.size();
		for (size_t i = 0; i != counter; ++i) {
			size_t u = list[t][i].tail;
			if (u == destinationVertex) {
				node[t].color = GREY;                                    
				++pathNum;
				Flag = false;
				printPath(path,destinationVertex);                                 // 打印每条路径
			}
			else if (node[u].color != BLACK) {
				myStack.push({ u, time });
				Flag = false;
			}                                                 
		}
		if (Flag == true) 
			node[t].color = BLACK;
		if (cnt == myStack.size()) {                                       // 记录路径
			if (!myStack.stackEmpty())
				while (!path.empty() && path.pop_back().time != myStack.top().time);                
			}	
	}
	//std::cout << "pathNum = " << pathNum  << " " << std::endl;
}
//**************************************************************************
//对有向无环图进行拓扑排序
bool compare(Vertex lhs, Vertex rhs) {
	if (lhs.fTime > rhs.fTime)
		return true;
	else
		return false;
}
void topologicalSort() {
	deepFirstSearch();
	auto beg = std::begin(node), tail = std::end(node);
	templa::quickSort(beg, tail, compare);
	for (size_t i = 0; i != vertexNum; ++i)
		std::cout << node[i].v << " ";
}
//***************************************************************************
//将有向图进行强联通分量分解
// 采用求两次dfs
//将有向图进行转置
void graphTransfer(templa::LinkList<Edge> list[]){
	size_t edgeNum[vertexNum];                         // 每个顶点相连的边个数
	for (size_t i = 0; i != vertexNum; ++i)
		edgeNum[i] = list[i].size();
	for (size_t i = 0; i != vertexNum; ++i){
		for (size_t j = 0; j != edgeNum[i]; ++j){
			Edge  t = list[i].pop_front();
			size_t vertex = t.tail;
			t.tail = i;
			list[vertex].push_back(t);
		}
	}
}
Color col[vertexNum] = { WHITE };
void stronglyConnectedComponents() {
	deepFirstSearch();                                     // 深度优先搜索
	auto beg = std::begin(node), tail = std::end(node);    
	templa::quickSort(beg, tail, compare);
	graphTransfer(list);                                   // 求转置图
	templa::Stack<size_t> myStack;
	for (size_t index = 0; index != vertexNum; ++index){
		myStack.push(node[index].v);                        
		while (!myStack.stackEmpty()) {
			size_t vertex = myStack.pop();
			if ( col[vertex] == WHITE) {
				col[vertex] = GREY;
				myStack.push(vertex);
				size_t counter = list[vertex].size();
				for (size_t i = 0; i != counter; ++i) {
					size_t t = list[vertex][counter - i - 1].tail;
					if (col[t] == WHITE) 
						myStack.push(t);
				}
			}
			else if (col[vertex] == GREY){
				col[vertex] = BLACK;
				std::cout << vertex << " ";
			}
		}
		std::cout << std::endl;
	}
 }

int main() {
	//DFS();
	//deepFirstSearch();
	//printDFS(std::cout, node, 6);
	//topologicalSort();
	//searchPath();
	//BFS();
	//printBFS(std::cout, node,6, 1);
	stronglyConnectedComponents();
	system("pause");
	return 0;
}