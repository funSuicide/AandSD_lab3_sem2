#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Graph.h"

int main() {
	City a("Moscow", 500000);
	City b("Minsk", 1000000);
	City c("Berlin", 10000000);
	City d("York", 20000);
	Graph T;
	T.AddVertex(a);
	T.AddVertex(b);
	T.AddVertex(c);
	T.AddVertex(d);
	T.AddEdge(a, b, 5000);
	T.AddEdge(b, c, 5000);
	T.AddEdge(c, d, 6000);
	T.PrintGraf();
	//T.DFS(b);
	T.BelmanFord(a, d);
}