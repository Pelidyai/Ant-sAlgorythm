#include "Graph.h"
#include <glut.h>
#include <iostream>
#include <Windows.h>
Graph::Graph(int count, int width, int height, double a, double b)
{
	this->alfa = a;
	this->betha = b;
	this->QPheramon = 400 / count;
	for (int i = 0; i < count; i++)
	{
		AllNodes.push_back(new Node((double)(rand() % (width-40) + 20), (double)(rand() % (height-40) + 20)));
	}
	SetWays();
}
void Graph::SetWays()
{
	int size = AllNodes.size();
	int countOfWays =0;
	int randIndex = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (i == j)
				continue;
			AllNodes.at(i)->ways.push_back(new Edges(AllNodes.at(i),\
													AllNodes.at(j), 0.1));
		}
	}
}
void Graph::DeleteSavedWays(vector<Edges*>& curWays, vector<Node*>& Saves)
{
	for (unsigned int j = 0; j < Saves.size(); j++)
		for (unsigned int i = 0; i < curWays.size(); i++)
		{
			if (curWays[i]->B == Saves[j])
			{
				curWays.erase(curWays.begin() + i);
				break;
			}
		}
}
void Graph::DrawGraph()
{
	for (unsigned int i = 0; i < this->AllNodes.size(); i++)
	{
		AllNodes.at(i)->DrawNode();
		for (unsigned int j = 0; j < AllNodes.at(i)->ways.size(); j++)
		{
			AllNodes.at(i)->ways.at(j)->DrawEdge(0);
		}
	}
}
void Graph::DrawMin()
{
	for (unsigned int j = 0; j < MinWay.size(); j++)
	{
		MinWay[j]->DrawEdge(1);
	}
}
double Graph::getLength(vector<Edges*> Way)
{
	double sum = 0;
	for (int i = 0; i < Way.size(); i++)
	{
		sum += Way[i]->length;
	}
	return sum;
}
double Graph::LetsGo()
{	
	double* Results = new double[AllNodes.size()];
	double min = INFINITE;
	int minInd =0;
	double cur = 0;
	vector<vector<Edges*>> Ways;
	for (unsigned int i = 0; i < AllNodes.size(); i++)
	{//встали муравьем
		Ways.push_back(RunAntRun(i));
	}
	for (unsigned int i = 0; i < AllNodes.size(); i++)
	{
		for (unsigned int j = 0; j < AllNodes[i]->ways.size(); j++)
		{
			AllNodes[i]->ways[j]->pheramon = Ipar* AllNodes[i]->ways[j]->pheramon;
		}
	}
	for (unsigned int i = 0; i < Ways.size(); i++)
	{
		for (unsigned int j = 0; j < Ways[i].size(); j++)
		{
			Ways[i][j]->pheramon += QPheramon / Ways[i][j]->length;
		}
	}
	for (unsigned int i = 0; i < Ways.size(); i++)
	{
		cur = getLength(Ways[i]);
		if (cur < min)
		{
			min = cur;
			minInd = i;
		}
	}
	for (unsigned int j = 0; j < Ways[minInd].size(); j++)
	{
		Ways[minInd][j]->pheramon += 5*QPheramon / Ways[minInd][j]->length;
	}
	this->MinWay = Ways[minInd];
	return getLength(Ways[minInd]);
}

vector<Edges*> Graph::RunAntRun(int index)
{
	unsigned int End = AllNodes.size() - 1;
	Node* curPoint = AllNodes[index];
	vector<Edges*> curWays;
	vector<Node*> Saves;
	vector<Edges*>SaveWays;
	double* PWays = nullptr;
	unsigned int Count = 0;
	double SumLenght = 0;
	while (End > Count)
	{
		double Summury = 0;
		curWays = curPoint->ways;
		DeleteSavedWays(curWays, Saves);
		if (PWays != NULL)
		{
			delete[] PWays;
			PWays = NULL;
		}
		PWays = new double[curWays.size() + 1];
		for (unsigned int i = 0; i < curWays.size(); i++)
		{
			Summury += pow(curWays[i]->pheramon, this->alfa)\
				* pow(1 / curWays[i]->length, this->betha);
		}
		if (Summury != 0 && !isnan(Summury))
		{
			PWays[0] = (pow(curWays[0]->pheramon, this->alfa)\
				* pow(1 / curWays[0]->length, this->betha)) / Summury;
			for (unsigned int i = 1; i < curWays.size(); i++)
			{
				PWays[i] = PWays[i - 1] + (pow(curWays[i]->pheramon, this->alfa)\
					* pow(1 / curWays[i]->length, this->betha)) / Summury;
			}
		}
		else
		{
			double del = curWays.size();
			PWays[0] = 1 / del;
			for (unsigned int i = 1; i < curWays.size(); i++)
			{
				PWays[i] = PWays[i - 1] + 1 / del;
			}
		}
		double P = rand() % 100;
		P /= 100;
		unsigned int i = 0;
		for (i = 0; i < curWays.size(); i++)
		{
			if (PWays[i] > P)
			{
				break;
			}
		}
		SaveWays.push_back(curWays[i]);
		Saves.push_back(curPoint);
		curPoint = curWays[i]->B;
		Count++;
	}
	for (unsigned int h = 0; h < curPoint->ways.size(); h++)
	{
		if (curPoint->ways[h]->B == AllNodes[index])
		{
			SaveWays.push_back(curPoint->ways[h]);
			break;
		}
	}
	return SaveWays;
}
//double Graph::RunAntRun(int index)
//{
//	unsigned int End = AllNodes.size() - 1;
//	Node* curPoint = AllNodes[index];
//	vector<Edges*> curWays;
//	vector<Node*> Saves;
//	double* PWays = nullptr;
//	unsigned int Count = 0;
//	double SumLenght = 0;
//	while (End > Count)
//	{
//		double Summury = 0;
//		curWays = curPoint->ways;
//		DeleteSavedWays(curWays, Saves);
//		if (PWays != NULL)
//		{
//			delete[] PWays;
//			PWays = NULL;
//		}
//		PWays = new double[curWays.size() + 1];
//		for (unsigned int i = 0; i < curWays.size(); i++)
//		{
//			Summury += pow(curWays[i]->pheramon, this->alfa)\
//				* pow(1 / curWays[i]->length, this->betha);
//		}
//		if (Summury != 0 && !isnan(Summury))
//		{
//			PWays[0] = (pow(curWays[0]->pheramon, this->alfa)\
//				* pow(1 / curWays[0]->length, this->betha)) / Summury;
//			for (unsigned int i = 1; i < curWays.size(); i++)
//			{
//				PWays[i] = PWays[i - 1] + (pow(curWays[i]->pheramon, this->alfa)\
//					* pow(1 / curWays[i]->length, this->betha)) / Summury;
//			}
//		}
//		else
//		{
//			double del = curWays.size();
//			PWays[0] = 1 / del;
//			for (unsigned int i = 1; i < curWays.size(); i++)
//			{
//				PWays[i] = PWays[i - 1] + 1 / del;
//			}
//		}
//		double P = rand() % 100;
//		P /= 100;
//		unsigned int i = 0;
//		for (i = 0; i < curWays.size(); i++)
//		{
//			if (PWays[i] > P)
//			{
//				break;
//			}
//		}
//		curWays[i]->pheramon += 0.03;
//		SumLenght += curWays[i]->length;
//		Saves.push_back(curPoint);
//		curPoint = curWays[i]->B;
//		Count++;
//	}	
//	for (int h = 0; h < curPoint->ways.size(); h++)
//	{
//		if (curPoint->ways[h]->B == AllNodes[index])
//		{
//			curPoint->ways[h]->pheramon += 0.1;
//			SumLenght += curPoint->ways[h]->length;
//			break;
//		}
//	}	
//	for (int k = 0; k < AllNodes.size(); k++)
//	{
//		for (int h = 0; h < AllNodes[k]->ways.size(); h++)
//		{
//			AllNodes[k]->ways[h]->pheramon -= 0.003;
//		}
//	}
//	return SumLenght;
//}

//void Graph::RunAntRun(int index)
//{
//	Node* curPoint = AllNodes[index];
//	vector<Edges*> curWays;
//	vector<Node*> Saves;
//	double* PWays = nullptr;
//	while (Saves.size()+1 != AllNodes.size())
//	{
//		double Summury = 0;
//		curWays = curPoint->ways;
//		for (unsigned int i = 0; i < curWays.size(); i++)
//		{
//			for (unsigned int j = 0; j < Saves.size(); j++)
//			{
//				if (curWays[i]->B == Saves[j])
//				{
//					curWays.erase(curWays.begin() + i);
//					if (i != 0)
//						i--;
//				}
//			}
//		}
//		if (PWays != NULL)
//		{
//			delete[] PWays;
//			PWays = NULL;
//		}
//		PWays = new double[curWays.size()];
//		for (unsigned int i = 0; i < curWays.size(); i++)
//		{
//			Summury += pow(curWays[i]->pheramon, this->alfa)\
//				* pow(1 / curWays[i]->length, this->betha);
//		}
//		if (Summury != 0&& !isnan(Summury))
//		{
//			PWays[0] = (pow(curWays[0]->pheramon, this->alfa)\
//				* pow(1 / curWays[0]->length, this->betha)) / Summury;
//			for (unsigned int i = 1; i < curWays.size(); i++)
//			{
//				PWays[i] = PWays[i - 1] + (pow(curWays[i]->pheramon, this->alfa)\
//					* pow(1 / curWays[i]->length, this->betha)) / Summury;
//			}
//		}
//		else
//		{
//			double del = curWays.size();
//			PWays[0] = 1 / del;
//			for (unsigned int i = 1; i < curWays.size(); i++)
//			{
//				PWays[i] = PWays[i - 1] + 1 / del;
//			}
//		}
//		double P = rand() % 100;
//		P /= 100;
//		unsigned int i = 0;
//		for (i = 0; i < curWays.size(); i++)
//		{
//			if (PWays[i] > P)
//			{
//				break;
//			}
//		}
//		curWays[i]->pheramon += 0.05;
//		Saves.push_back(curPoint);
//		curPoint = curWays[i]->B;
//		
//		//for(unsigned int j =0; j<curPoint)
//	}
//	//Sleep(1000);
//	//glutPostRedisplay();
//	for (int k = 0; k < AllNodes.size(); k++)
//	{
//		for (int h = 0; h < AllNodes[k]->ways.size(); h++)
//		{
//			AllNodes[k]->ways[h]->pheramon -= 0.01;
//		}
//	}
//	unsigned int i = 0;
//	if (curPoint != AllNodes[index])
//	{
//		for (; i < curPoint->ways.size(); i++)
//		{
//			if (curPoint->ways[i]->B == AllNodes[index])
//			{
//				break;
//			}
//		}
//		curPoint->ways[i]->pheramon += 0.05;
//	}
//}

//void Graph::RunAntRun(int index)
//{
//	Node* curPoint = AllNodes[index];
//	vector<Node*> Saves;
//	bool isRepeat = false;
//	double Summury = 0;
//	double* PWays = new double[AllNodes.size()];
//	while (Saves.size() != AllNodes.size())
//	{
//		Summury = 0;
//		for (unsigned int i = 0; i < curPoint->ways.size(); i++)
//		{
//			for (unsigned int j = 0; j < Saves.size(); j++)
//				if (curPoint->ways[i]->B == Saves[j])
//				{
//					isRepeat = true;
//					break;
//				}
//			if (isRepeat)
//			{
//				isRepeat = false;
//				continue;
//			}
//			else
//			{
//				Summury += pow(curPoint->ways[i]->pheramon, this->alfa)\
//					* pow(1 / curPoint->ways[i]->length, this->betha);
//			}
//		}
//
//		for (unsigned int i = 0; i < AllNodes.size()-1; i++)
//		{
//			for (unsigned int j = 0; j < Saves.size(); j++)
//				if (curPoint->ways[i]->B == Saves[j])
//				{
//					isRepeat = true;
//					break;
//				}
//			if (isRepeat)
//			{
//				isRepeat = false;
//				PWays[i] = 0;
//				continue;
//			}
//			else
//			{
//				if (i == 0)
//					PWays[i] = (pow(curPoint->ways[i]->pheramon, this->alfa)\
//						* pow(1 / curPoint->ways[i]->length, this->betha)) / Summury;
//				else
//					PWays[i] = PWays[i - 1] + (pow(curPoint->ways[i]->pheramon, this->alfa)\
//						* pow(1 / curPoint->ways[i]->length, this->betha)) / Summury;
//			}
//		}
//		double P = rand() % 100;
//		P /= 100;
//		unsigned int i = 0;
//		if (Summury == 0)
//		{
//			int del = AllNodes.size() - 1 - Saves.size();
//			if (del != 0)
//			{
//				PWays[0] = 1 / del;
//				for (i = 1; i < AllNodes.size() - 1 - Saves.size(); i++)
//				{
//					PWays[i] = PWays[i - 1] + 1 / del;
//				}
//			}
//			else
//			{
//				printf("else");
//			}
//		}
//		for (i=0; i < AllNodes.size() - 1 - Saves.size(); i++)
//		{
//			if (PWays[i] > P)
//			{
//				break;
//			}
//		}
//		Saves.push_back(curPoint);
//		curPoint->ways[i]->pheramon += 0.05;
//		curPoint = curPoint->ways[i]->B;
//	}
//	for (int k = 0; k < AllNodes.size(); k++)
//	{
//		for (int h = 0; h < AllNodes[k]->ways.size(); h++)
//		{
//			AllNodes[k]->ways[h]->pheramon -= 0.01;
//		}
//	}
//}