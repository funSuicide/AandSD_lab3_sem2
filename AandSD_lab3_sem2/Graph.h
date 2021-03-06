#include <vector>
#include "City.h"
#include <algorithm>
#include <stack>

class Graph {
	std::vector<City>vertex;
	struct Edge {
		int edgeSource;
		int edgeDest;
		double edgeWeight;
		Edge(int tmpSource, int tmpDest, double tmpWeight) {
			edgeSource = tmpSource;
			edgeDest = tmpDest;
			edgeWeight = tmpWeight;
		}
	};
	std::vector<Edge>edges;
	int GetIdVertex(City& tmpCity) {
		for (int i = 0; i < vertex.size(); ++i) {
			if (vertex[i] == tmpCity) return i;
		}
		return -1;
	}
	double GetLenghWays(int source, int dest){
		for (auto& it : edges){
			if (it.edgeSource == source && it.edgeDest == dest)
				return it.edgeWeight;
		}
		return INT_MAX * 1.0;
	}
public:
	void AddVertex(City& tmpVertex) {
		if (GetIdVertex(tmpVertex) < 0) {
			vertex.push_back(tmpVertex);
		}
		else {
			throw "This vertex is already exist!";
		}
	} 

	void DeleteVertex(City& tmpVertex) {
		int index = GetIdVertex(tmpVertex);
		if (index < 0) {
			throw "This vertex is does not exist!";
		}
		vertex.erase(vertex.begin() + index);
		int indexEdge = -1;
		for (int i = 0; i < edges.size(); i++) {
			if (edges[i].edgeSource == index || edges[i].edgeDest == index){
				indexEdge = i;
				break;
			}
		}
		edges.erase(edges.begin() + indexEdge);
	}

	void AddEdge(City& sourceCity, City& destCity, double weight){
		int tmpSource = GetIdVertex(sourceCity);
		int tmpDest = GetIdVertex(destCity);
		if (tmpSource < 0) throw "Source does not exist";
		if (tmpDest < 0) throw "Destination does not exist";
		Edge newEdge(tmpSource, tmpDest, weight);
		edges.push_back(newEdge);
	}

	void DeleteEdge(City& sourceCity, City& destCity) {
		int tmpSource = GetIdVertex(sourceCity);
		int tmpDest = GetIdVertex(destCity);
		for (int i = 0; i < edges.size(); i++) {
			if ((edges[i].edgeSource == tmpSource) && (edges[i].edgeDest == tmpDest)) {
				edges.erase(edges.begin() + i);
				return;
			}
		}
		throw "Edge does not exist!";
	}

	std::vector<std::vector<int>> AdjList(){
		std::vector<std::vector<int>>adj(vertex.size(), std::vector<int>());
		for (int i = 0; i < edges.size(); i++)
		{
			adj[edges[i].edgeSource].push_back(edges[i].edgeDest);
		}
		return adj;
	}

	void PrintGraf(){
		std::vector<std::vector<int>>adjList = AdjList();
		for (int i = 0; i < adjList.size(); i++){
			vertex[i].PrintCity();
			std::cout << " ";
			for (auto it : adjList[i]){
				std::cout << "[";
				vertex[it].PrintCity();
				std::cout << " LenghtWay: " << GetLenghWays(i, it) << "]  ";
			}
			std::cout << std::endl;
		}
	}

	void DFS(City& tmpCity){
		int s = GetIdVertex(tmpCity);
		if (s == -1){
			throw "This vertex netu!";
		}
		std::vector<std::vector<int>>adj = AdjList();
		std::vector<bool> visited(vertex.size(), false);
		std::stack<int> stack;
		stack.push(s);
		while (!stack.empty()){
			int s = stack.top();
			stack.pop();
			if (!visited[s]){
				std::cout << "(" << vertex[s].GetName() << ")" << "->";
				visited[s] = true;
			}
			for (auto i : adj[s]) {
				if (!visited[i]) {
					stack.push(i);
				}
			}
		}
	}

	void BelmanFord(City& citySource, City& cityDes){
		int INF = INT_MAX;
		std::vector<int> vecFirst(vertex.size(), INF); //1. ?????????? ?? citySource ?? ????????? ?????? = ?????????????
		int start = GetIdVertex(citySource);
		int end = GetIdVertex(cityDes);  //2. ???????? ??????? ????????? ? ?????????
		if (start == -1 || end == -1){
			throw "Error!";
		}

		vecFirst[start] = 0; //3. ? ?????? citySource = 0
		std::vector<int> vecSecond(vertex.size(), -1);
		for (;;) {
			bool any = false;
			for (int j = 0; j < edges.size(); ++j)
				if (vecSecond[edges[j].edgeSource] < INF)
					if (vecFirst[edges[j].edgeDest] > vecFirst[edges[j].edgeSource] + edges[j].edgeWeight) {
						vecFirst[edges[j].edgeDest] = vecFirst[edges[j].edgeSource] + edges[j].edgeWeight;
						vecSecond[edges[j].edgeDest] = edges[j].edgeSource;
						any = true;
					}
			if (!any)  break;
		}

		if (vecFirst[end] == INF)
			std::cout << "No path from " << vertex[start].GetName() << " to " << vertex[end].GetName() << ".";
		else {
			std::vector<int> path;
			double summ = 0;
			for (int cur = end; cur != -1; cur = vecSecond[cur]) {
				path.push_back(cur);
			}
			reverse(path.begin(), path.end());
			std::cout << "Path from " << vertex[start].GetName() << " to " << vertex[end].GetName() << ": ";
			for (size_t i = 0; i < path.size()-1; ++i)
				std::cout << vertex[path[i]].GetName() << "-->";
			std::cout << vertex[path.size() - 1].GetName();
			std::cout << std::endl;
			std::cout << "Summary lenght way is : " << vecSecond[end]+1 << std::endl;
		}
	}
};