#include <iostream>
#include <string>
#include <cmath>
#include "Cellule.h"


Cellule::Cellule()
{
	position_x = -1;
	position_y = -1;
	couleur = blanc;
	representant = NULL;
}

Cellule::Cellule(int x, int y, Cellule::couleur_case coul, Cellule* ptr)
{
	position_x = x;
	position_y = y;
	couleur = coul;
	representant = ptr;
}

Cellule Cellule::get_representant()
{
	if(representant == NULL)
	{
		return *this;
	}
	else
	{
		return *representant;
	}
}

Cellule::Cellule(Cellule const& cellulecopie): position_x(cellulecopie.position_x), position_y(cellulecopie.position_y), 
couleur(cellulecopie.couleur), nb_possibilite_cellule(cellulecopie.nb_possibilite_cellule), representant(cellulecopie.representant){}

int Cellule::get_position_x(){return position_x;}
int Cellule::get_position_y(){return position_y;}
Cellule::couleur_case Cellule::get_couleur(){return couleur;}
void Cellule::set_couleur(Cellule::couleur_case coul){couleur = coul;}
void Cellule::set_position_x(int x){position_x = x;}
void Cellule::set_position_y(int y){position_y = y;}
int Cellule::get_nb_possibilite_cellule(){return nb_possibilite_cellule;}
void Cellule::set_nb_possibilite_cellule(int nombre){nb_possibilite_cellule = nombre;}
void Cellule::set_representant(Cellule* cellule_ile){representant = cellule_ile;}
