#include <iostream>
#include <string>
#include <cmath>
#include "Ile.h"


Ile::Ile()
{
	position_x = -1;
	position_y = -1;
	numero_cellule = 0;
	compteur = 0;
	nb_possibilite_ile = 0;
}

Ile::Ile(int x, int y, int numero)
{
	position_x = x;
	position_y = y;
	numero_cellule = numero;
	compteur = 1;
	
	if(x > 0 && x < 7)
	{
		if(y > 0 && y < 5)
			nb_possibilite_ile = 4;
		else 
			nb_possibilite_ile = 3;
	}
	else
	{
		if(y > 0 && y < 5)
			nb_possibilite_ile = 3;
		else 
			nb_possibilite_ile = 2;
	}
}

int Ile::get_position_x(){return position_x;}
int Ile::get_position_y(){return position_y;}
int Ile::get_numero_cellule(){return numero_cellule;}
int Ile::get_compteur(){return compteur;}
void Ile::set_position_x(int x){position_x = x;}
void Ile::set_position_y(int y){position_y = y;}
void Ile::set_numero_cellule(int numero){numero_cellule = numero;}
void Ile::set_compteur(int nb){compteur = nb;}
int Ile::get_nb_possibilite_ile(){return nb_possibilite_ile;}
void Ile::set_nb_possibilite_ile(int nombre){nb_possibilite_ile = nombre;}