#include "Edges.h"
#include <glut.h>
Edges::Edges()
{
	length = 0;
	pheramon = 0;
	A = NULL, B = NULL;
}
Edges::Edges(Edges& base)
{
	this->length = base.length;
	this->pheramon = base.pheramon;
	this->A = base.A;
	this->B = base.B;
}
Edges::Edges(Node* A, Node* B, double defaultPheramon)
{
	length = sqrt((A->position.x - B->position.x)\
		* (A->position.x - B->position.x)\
		+ (A->position.y - B->position.y)\
		* (A->position.y - B->position.y));
	pheramon = defaultPheramon;
	this->A = A;
	this->B = B;
}
void Edges::DrawEdge( bool r)
{
	if (this->pheramon < 0)
		this->pheramon = 0;
	else
	{
		if (!r)
		{
			glColor4d(0, 1, 0, this->pheramon);
			glLineWidth(this->pheramon);
			glBegin(GL_LINES);
			glVertex2d(this->A->position.x, this->A->position.y);
			glVertex2d(this->B->position.x, this->B->position.y);
			glEnd();
		}
		else
		{
			glColor3d(1, 0, 0);
			glLineWidth(2);
			glBegin(GL_LINES);
			glVertex2d(this->A->position.x, this->A->position.y);
			glVertex2d(this->B->position.x, this->B->position.y);
			glEnd();
		}
			
	}
}