#include "Node.h"
#include <glut.h>
Node::Node()
{
	position.x = 0, position.y = 0;
}
Node::Node(double x, double y)
{
	position.x = x, position.y = y;
}
Node::Node(Node& base)
{
	this->position.x = base.position.x;
	this->position.y = base.position.y;
	for (unsigned int i = 0; i < base.ways.size(); i++)
	{
		this->ways.push_back(base.ways.at(i));
	}
}
void Node::DrawNode()
{
	glTranslated(this->position.x, this->position.y, 0);
	glColor3ub(0, 255, 0);
	GLUquadricObj* obj = gluNewQuadric();
	gluDisk(obj, 0, 10, 20, 1);
	glColor3ub(1, 1, 1);
	//char a = '1';
	//glutBitmapCharacter(GLUT_STROKE_ROMAN, a);
	glTranslated(-this->position.x, -this->position.y, 0);
}
