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
		return 0;
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
		for (int i = 0; i < edges.size(); ++i) {
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
		for (int i = 0; i < edges.size(); ++i) {
			if ((edges[i].edgeSource = tmpSource) && (edges[i].edgeDest = tmpDest)) {
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
			for (auto it : adjList[i]){
				std::cout << "[ ";
				vertex[it].PrintCity();
				std::cout << "LenghtWay: " << GetLenghWays(i, it) << " ]  ";
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
				std::cout << "(**" << vertex[s].GetName() << "**)" << "->";
				visited[s] = true;
			}
			for (auto i : adj[s]) {
				if (!visited[i]) {
					stack.push(i);
				}
			}
		}
	}
};