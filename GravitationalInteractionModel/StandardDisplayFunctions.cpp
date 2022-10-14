#include "StandardDisplayFunctions.h"

void displayCircle(double x, double y, double r)
{

	int amountSegments = 50;

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < amountSegments; i++)
	{
		float angle = 2.0 * 3.1415926 * float(i) / float(amountSegments);

		float dx = r * cosf(angle);
		float dy = r * sinf(angle);

		glVertex2f(x + dx, y + dy);
	}

	glEnd();
}