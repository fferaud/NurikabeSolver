#ifndef CELLULE_H
#define CELLULE_H
#include <iostream>
#include <string>


class Cellule
{
	public:
		enum couleur_case
		{
			blanc = 0,
			noir = 1,
			grise = 2,
			ile = 3,
			ruisseau = 4
		};

		Cellule();
		Cellule(int, int, couleur_case, Cellule*);
		Cellule(Cellule const&); // Constructeur par copie

		int get_position_x();
		int get_position_y();
		couleur_case get_couleur();
		int get_nb_possibilite_cellule();
		Cellule get_representant();
		void set_representant(Cellule*);
		void set_position_x(int);
		void set_position_y(int);
		void set_couleur(couleur_case);
		void set_nb_possibilite_cellule(int);

	private:
		int position_x;
		int position_y;
		couleur_case couleur;
		int nb_possibilite_cellule;
		Cellule* representant;
};

#endif