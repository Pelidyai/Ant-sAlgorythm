#pragma once
#include <vector>
#include "Point.h"
#include "Edges.h"
class Edges;
class Node
{
	static const int radius = 10;
	friend class Edges;
	friend class Graph;
	Point position;
	std::vector<Edges*> ways;
	Node();
	Node(Node&);
	Node(double x, double y);
	void DrawNode();
};

