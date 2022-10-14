#include "LogicCycle.h"
#include "initOpenGL.h"
#include "Factory.h"

#include "Planet.h"
#include <string>

#define TIME (1.0 / 10000.0)

double random(double min, double max)
{
	double c = (rand() % 10001) * 0.0001; // 0..1
	double result = min + (max - min) * c;

	return result;
}

double randomSign()
{
	double result = (rand() % 2) * 2 - 1;
	return result;
}



void logicCycle()
{
	Factory<Planet>& planets = Factory<Planet>::getInst();

	auto calculate = [&planets]()
	{
		double time =  TIME * pow(10, -5.5) * 365*24*60;
		const double G = 6674301515;

		for (int i = 0; i < planets.size(); i++)
		{

			VectorP coord = planets[i].Coord() + planets[i].Vel() * time + planets[i].Acc() * time * time;
			VectorP vel = planets[i].Vel() + planets[i].Acc() * time;
			VectorP acc = {};

			for (int j = 0; j < planets.size(); j++)
			{
				if (i == j)
					continue;

				double R2 = planets[i].Coord().distance2(planets[j].Coord());

				double F = 0;
				if (R2 != 0)
					F = G * planets[i].Mass() * planets[j].Mass() / R2;
				else
					F = 0;
			
				VectorP directionVector = 0;

				if (planets[i].Coord().distance2(planets[j].Coord()) != 0)
				{
					directionVector = (planets[j].Coord() - planets[i].Coord()) / sqrt(planets[i].Coord().distance2(planets[j].Coord()));
				}
				else
					directionVector = 0;

				acc = acc + directionVector * F / (planets[i].Mass() * pow(10, 21));

			}

			planets[i].setCoord(coord);
			planets[i].setVel(vel);
			planets[i].setAcc(acc);

			/*static int i = 0;
			i++;
			if (i == 100000)
			{
				MessageBoxA(NULL, (std::to_string(planets[0].Coord().X()) + " " + std::to_string(planets[0].Coord().Y())).c_str(), std::to_string(time).c_str(), MB_ICONERROR);
				i = 0;
			}*/

		}
	};


	while (true)
	{
		if (wait(1.0 / TIME) == 0)
			continue;

		calculate();

		//Sleep(1);
	}
}
