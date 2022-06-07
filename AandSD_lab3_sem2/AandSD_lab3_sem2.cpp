#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "Graph.h"

int main() {
	Graph T;
	City a("Moscow", 12000000);
	City b("Berlin", 3600000);
	City c("Tokyo", 14000000);
	City d("Minsk", 2000000);
	City f("Samara", 2700000);
	City e("Buzuluk", 90000);

	T.AddVertex(a);
	T.AddVertex(b);
	T.AddVertex(c);
	T.AddVertex(d);
	T.AddVertex(e);
	T.AddVertex(f);

	T.AddEdge(a, b, 5000);
	T.AddEdge(a, f, 1000);
	T.AddEdge(f, e, 300);
	T.AddEdge(e, b, 2000);
	T.AddEdge(d, c, 500);

	T.PrintGraf();
	std::cout << std::endl;

	T.DeleteEdge(f, e);
	T.DeleteEdge(e, b);
	T.AddEdge(c, d, -500);
	
	T.PrintGraf();
	std::cout << std::endl;

	T.AddEdge(b, c, 3000);
	T.AddEdge(d, e, 150);
	T.AddEdge(d, f, 1000);

	T.PrintGraf();
	std::cout << std::endl;
	T.DFS(b);

	std::cout << std::endl;
	T.BelmanFord(a, e);
	std::cout << std::endl;

	T.AddEdge(a, e, 1000);
	T.BelmanFord(a, e);
}