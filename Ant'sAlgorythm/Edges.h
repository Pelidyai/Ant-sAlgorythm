#pragma once
#include "Node.h"
class Node;
class Edges
{
	friend class Graph;
	double length;
	double pheramon;
	Node* A;
	Node* B;
	Edges();
	Edges(Edges&);
	Edges(Node*, Node*, double);
	void DrawEdge(bool);
};

