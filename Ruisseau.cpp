#include <iostream>
#include <string>
#include <cmath>
#include "Ruisseau.h"
#include "Cellule.h"

Ruisseau::Ruisseau()
{
	position_x = -1;
	position_y = -1;
}

Ruisseau::Ruisseau(int x, int y)
{
	position_x = x;
	position_y = y;

	if(x > 0 && x < 7)
	{
		if(y > 0 && y < 5)
			nb_possibilite_ruisseau = 4;
		else 
			nb_possibilite_ruisseau = 3;
	}
	else
	{
		if(y > 0 && y < 5)
			nb_possibilite_ruisseau = 3;
		else 
			nb_possibilite_ruisseau = 2;
	}
}

int Ruisseau::get_position_x(){return position_x;}
int Ruisseau::get_position_y(){return position_y;}
void Ruisseau::set_position_x(int x){position_x = x;}
void Ruisseau::set_position_y(int y){position_y = y;}
int Ruisseau::get_nb_possibilite_ruisseau(){return nb_possibilite_ruisseau;}
void Ruisseau::set_nb_possibilite_ruisseau(int nombre){nb_possibilite_ruisseau = nombre;}
