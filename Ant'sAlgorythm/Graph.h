#include <vector>
#include <random>
#include "Node.h"
using namespace std;
#pragma once
class Graph
{	
public:
	Graph(int count, int width, int height, double alfa, double betha);
	void DrawGraph();
	double LetsGo();
	vector<Edges*> RunAntRun(int);
	void DrawMin();

private:
	vector<Edges*> MinWay;
	double alfa, betha;
	double QPheramon = 20;
	const double Ipar = 0.1;
	vector<Node*> AllNodes;
	void SetWays();
	double getLength(vector<Edges*>);
	void DeleteSavedWays(vector<Edges*>&, vector<Node*>&);

};
