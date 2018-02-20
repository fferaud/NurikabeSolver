#ifndef ILE_H
#define ILE_H
#include <iostream>
#include <string>
#include <vector>
#include "Cellule.h"

class Ile
{
	public:
		Ile();
		Ile(int, int, int);

		std::vector<Cellule> tableau_chemin_ile;
		int get_position_x();
		int get_position_y();
		int get_numero_cellule();
		int get_compteur();
		int get_nb_possibilite_ile();
		void set_position_x(int);
		void set_position_y(int);
		void set_numero_cellule(int);
		void set_compteur(int);
		void set_nb_possibilite_ile(int);

	private:
		int position_x;
		int position_y;
		int numero_cellule;
		int compteur; //nombre de case placer pour l'île
		int nb_possibilite_ile;
};

#endif