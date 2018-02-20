#ifndef RUISSEAU_H
#define RUISSEAU_H
#include <iostream>
#include <string>
#include <vector>
#include "Cellule.h"

class Ruisseau
{
	public:
		Ruisseau();
		Ruisseau(int, int);

		std::vector<Cellule> tableau_chemin_ruisseau;
		int get_position_x();
		int get_position_y();
		int get_nb_possibilite_ruisseau();
		void set_position_x(int);
		void set_position_y(int);
		void set_nb_possibilite_ruisseau(int);

	private:
		int position_x;
		int position_y;
		int nb_possibilite_ruisseau;
};

#endif