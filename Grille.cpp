#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "Grille.h"
#include "Cellule.h"

Grille::Grille(){}

Grille::Grille(int largeur, int longueur):grille(largeur, std::vector<Cellule>(longueur, Cellule(0,0,Cellule::blanc, NULL))), largeur(largeur), longueur(longueur)
{
	for(int x = 0; x < largeur; x++)
	{
		for(int y = 0; y < longueur; y++)
		{
			grille[x][y].set_position_x(x);
			grille[x][y].set_position_y(y);
		}
	}
}

/* Partie 1) S'occupe de remplir de case autour des iles à 1. Partie 2) S'occupe de poser une case grise et de compléter si une île n'a plus qu'une possibilitée
   de positionnement sur la grille */
void Grille::completer_case() 
{
	int position_x, position_y, position_ile_x, position_ile_y;
	for(int i = 0; i < tableau_ile.size(); i++)
	{
		position_x = tableau_ile[i].get_position_x();
		position_y = tableau_ile[i].get_position_y();

		if(tableau_ile[i].get_numero_cellule() == 1) // Dans le cas où l'île est de 1
		{
			if(position_x + 1 < largeur)
			{
				this->grille[position_x + 1][position_y].set_couleur(Cellule::noir);
				creation_element_tableau_ruisseau(position_x + 1, position_y); //création d'une île noire
			}

			if(position_x - 1 > 0)
			{
				this->grille[position_x - 1][position_y].set_couleur(Cellule::noir);
				creation_element_tableau_ruisseau(position_x - 1, position_y); //création d'une île noire
			}

			if(position_y + 1 < longueur)
			{
				this->grille[position_x][position_y + 1].set_couleur(Cellule::noir);
				creation_element_tableau_ruisseau(position_x, position_y + 1); //création d'une île noire
			}

			if(position_y - 1 > 0)
			{
				this->grille[position_x][position_y - 1].set_couleur(Cellule::noir);
				creation_element_tableau_ruisseau(position_x, position_y - 1); 
			}
		}

		/* Complète une ile si il ne lui reste qu'une possibilité de placement */
		//std::cout << "compteur = " << tableau_ile[i].get_compteur() << std::endl;
		//std::cout << "cellule = " <<  tableau_ile[i].get_numero_cellule() << std::endl;
		//std::cout << "possibilite = " << tableau_ile[i].get_nb_possibilite_ile() << std::endl;
		if(tableau_ile[i].get_compteur() == tableau_ile[i].get_numero_cellule() - 1 && tableau_ile[i].get_nb_possibilite_ile() == 1)
		{
			if(position_x + 1 < largeur)
			{
				if(this->grille[position_x + 1][position_y].get_couleur() == Cellule::blanc) //Droite
				{
					this->grille[position_x + 1][position_y].set_couleur(Cellule::grise);  // Mets la case en gris pour l'ile
					this->grille[position_x + 1][position_y].set_representant(&grille[position_x][position_y]); // Mets le représentant de la cellule à jour
					this->tableau_ile[i].tableau_chemin_ile.push_back(this->grille[position_x + 1][position_y]); // Rajoute la case grise dans le tableau de l'ile en question
					this->tableau_ile[i].set_compteur(this->tableau_ile[i].get_compteur() + 1); // mets le compteur à jour
					this->tableau_ile[i].set_nb_possibilite_ile(this->tableau_ile[i].get_nb_possibilite_ile() - 1); // mets les possibilités de placement à jour

					/*Permet de compléter l'espace autour de la case grise avec des cases noires (création de ruisseau et ajustement de leur nb de possibilité pris en compte)*/
					if (this->grille[position_x + 2][position_y].get_couleur() == Cellule::blanc && position_x < largeur)
					{
						this->grille[position_x + 2][position_y].set_couleur(Cellule::noir);  //mets la case en noire
						creation_element_tableau_ruisseau(position_x + 2, position_y); // crée un ruisseau + ajuste son nb de possibilité
					}

					if (this->grille[position_x + 1][position_y + 1].get_couleur() == Cellule::blanc && position_y + 1 < longueur)
					{
						this->grille[position_x + 1][position_y + 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_x + 1, position_y + 1);	
					}

					if(this->grille[position_x + 1][position_y - 1].get_couleur() == Cellule::blanc && position_y - 1 > 0)
					{
						this->grille[position_x + 1][position_y - 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_x + 1, position_y - 1);
					}
				}
			}

			if(position_x - 1 > 0)
			{
				if(this->grille[position_x - 1][position_y].get_couleur() == Cellule::blanc) //Gauche
				{
					this->grille[position_x - 1][position_y].set_couleur(Cellule::grise);
					this->grille[position_x - 1][position_y].set_representant(&grille[position_x][position_y]);
					this->tableau_ile[i].tableau_chemin_ile.push_back(this->grille[position_x - 1][position_y]);
					this->tableau_ile[i].set_compteur(this->tableau_ile[i].get_compteur() + 1);
					this->tableau_ile[i].set_nb_possibilite_ile(this->tableau_ile[i].get_nb_possibilite_ile() - 1);

					if (this->grille[position_x - 2][position_y].get_couleur() == Cellule::blanc && position_x - 2 > 0)
					{
						this->grille[position_x - 2][position_y].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_x - 2, position_y);
					}

					if (this->grille[position_x - 1][position_y + 1].get_couleur() == Cellule::blanc && position_y + 1 < longueur)
					{
						this->grille[position_x - 1][position_y + 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_x - 1, position_y + 1);	
					}

					if(this->grille[position_x - 1][position_y - 1].get_couleur() == Cellule::blanc && position_y - 1 > 0)
					{
						this->grille[position_x - 1][position_y - 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_x - 1, position_y - 1);
					}
				}
			}

			if(position_y + 1 < longueur)
			{
				if(this->grille[position_x][position_y + 1].get_couleur() == Cellule::blanc) //Haut
				{
					this->grille[position_x][position_y + 1].set_couleur(Cellule::grise);
					this->grille[position_x][position_y + 1].set_representant(&grille[position_x][position_y]);
					this->tableau_ile[i].tableau_chemin_ile.push_back(this->grille[position_x][position_y + 1]);
					this->tableau_ile[i].set_compteur(this->tableau_ile[i].get_compteur() + 1);
					this->tableau_ile[i].set_nb_possibilite_ile(this->tableau_ile[i].get_nb_possibilite_ile() - 1);

					if (this->grille[position_x][position_y + 2].get_couleur() == Cellule::blanc && position_y + 2 < longueur)
					{
						this->grille[position_x][position_y + 2].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_x, position_y + 2);
					}

					if (this->grille[position_x - 1][position_y + 1].get_couleur() == Cellule::blanc && position_x - 1 > 0)
					{
						this->grille[position_x - 1][position_y + 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_x - 1, position_y + 1);	
					}

					if(this->grille[position_x + 1][position_y + 1].get_couleur() == Cellule::blanc && position_x + 1 < largeur)
					{
						this->grille[position_x + 1][position_y + 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_x + 1, position_y + 1);
					}
				}
			}
				
			if(position_y - 1 > 0)
			{
				if(this->grille[position_x][position_y - 1].get_couleur() == Cellule::blanc) //Bas
				{
					this->grille[position_x][position_y - 1].set_couleur(Cellule::grise);
					this->grille[position_x][position_y - 1].set_representant(&grille[position_x][position_y]);
					this->tableau_ile[i].tableau_chemin_ile.push_back(this->grille[position_x][position_y - 1]);
					this->tableau_ile[i].set_compteur(this->tableau_ile[i].get_compteur() + 1);
					this->tableau_ile[i].set_nb_possibilite_ile(this->tableau_ile[i].get_nb_possibilite_ile() - 1);

					if (this->grille[position_x][position_y - 2].get_couleur() == Cellule::blanc && position_y - 2 > 0)
					{
						this->grille[position_x][position_y - 2].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_x, position_y - 2);
					}

					if (this->grille[position_x - 1][position_y - 1].get_couleur() == Cellule::blanc && position_x - 1 > 0)
					{
						this->grille[position_x - 1][position_y - 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_x - 1, position_y - 1);	
					}

					if(this->grille[position_x + 1][position_y - 1].get_couleur() == Cellule::blanc && position_x + 1 < largeur)
					{
						this->grille[position_x + 1][position_y - 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_x + 1, position_y - 1);
					}
				}
			}
		}

		/*Dans le cas ou il faut entourer de cases noires une île qui ess terminée*/
		if(tableau_ile[i].get_compteur() == tableau_ile[i].get_numero_cellule())
		{
			/*Remplis de cases noires autour de l'ile en question*/
			if(position_x + 1 < largeur)
			{
				if(this->grille[position_x + 1][position_y].get_couleur() == Cellule::blanc) //Droite
				{
					this->grille[position_x + 1][position_y].set_couleur(Cellule::noir);
					creation_element_tableau_ruisseau(position_x + 1, position_y);
					this->tableau_ile[i].set_nb_possibilite_ile(this->tableau_ile[i].get_nb_possibilite_ile() - 1);
				}
			}

			if(position_x - 1 > 0)
			{
				if(this->grille[position_x - 1][position_y].get_couleur() == Cellule::blanc) //gauche
				{
					this->grille[position_x - 1][position_y].set_couleur(Cellule::noir);
					creation_element_tableau_ruisseau(position_x - 1, position_y);
					this->tableau_ile[i].set_nb_possibilite_ile(this->tableau_ile[i].get_nb_possibilite_ile() - 1);
				}
			}

			if(position_y + 1 < longueur)
			{
				if(this->grille[position_x][position_y + 1].get_couleur() == Cellule::blanc) //haut
				{
					this->grille[position_x][position_y + 1].set_couleur(Cellule::noir);
					creation_element_tableau_ruisseau(position_x, position_y + 1);
					this->tableau_ile[i].set_nb_possibilite_ile(this->tableau_ile[i].get_nb_possibilite_ile() - 1);
				}
			}

			if(position_y - 1 > 0)
			{
				if(this->grille[position_x][position_y - 1].get_couleur() == Cellule::blanc) //bas
				{
					this->grille[position_x][position_y - 1].set_couleur(Cellule::noir);
					creation_element_tableau_ruisseau(position_x, position_y - 1);
					this->tableau_ile[i].set_nb_possibilite_ile(this->tableau_ile[i].get_nb_possibilite_ile() - 1);
				}
			}

			/*Remplissage de cases noires autour des fils de l'île*/
			for(int j = 0; j < tableau_ile[i].tableau_chemin_ile.size(); j++)
			{
				position_ile_x = tableau_ile[i].tableau_chemin_ile[j].get_position_x();
				position_ile_y = tableau_ile[i].tableau_chemin_ile[j].get_position_y();

				if(position_ile_x + 1 < largeur)
				{
					if(this->grille[position_ile_x + 1][position_ile_y].get_couleur() == Cellule::blanc) //Droite
					{
						this->grille[position_ile_x + 1][position_ile_y].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_ile_x + 1, position_ile_y);
						this->tableau_ile[i].tableau_chemin_ile[j].set_nb_possibilite_cellule(this->tableau_ile[i].tableau_chemin_ile[j].get_nb_possibilite_cellule() - 1);
					}
				}

				if(position_ile_x - 1 > 0)
				{
					if(this->grille[position_ile_x - 1][position_ile_y].get_couleur() == Cellule::blanc) //gauche
					{
						this->grille[position_ile_x - 1][position_ile_y].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_ile_x - 1, position_ile_y);
						this->tableau_ile[i].tableau_chemin_ile[j].set_nb_possibilite_cellule(this->tableau_ile[i].tableau_chemin_ile[j].get_nb_possibilite_cellule() - 1);
					}
				}

				if(position_ile_y + 1 < longueur)
				{
					if(this->grille[position_ile_x][position_y + 1].get_couleur() == Cellule::blanc) //bas
					{
						this->grille[position_ile_x][position_ile_y + 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_ile_x, position_ile_y + 1);
						this->tableau_ile[i].tableau_chemin_ile[j].set_nb_possibilite_cellule(this->tableau_ile[i].tableau_chemin_ile[j].get_nb_possibilite_cellule() - 1);
					}
				}

				if(position_ile_y - 1 > 0)
				{
					if(this->grille[position_ile_x][position_ile_y - 1].get_couleur() == Cellule::blanc) //haut
					{
						this->grille[position_ile_x][position_ile_y - 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_ile_x, position_ile_y - 1);
						this->tableau_ile[i].tableau_chemin_ile[j].set_nb_possibilite_cellule(this->tableau_ile[i].tableau_chemin_ile[j].get_nb_possibilite_cellule() - 1);
					}
				}
			}
		}
	}
}

/* Partie 1) S'occupe du cas où une ile est dans la diagonale / Partie 2) S'occupe du cas où une île est sur les côtés à une distance de 2 */
/* Je ne sais pas encore comment mettre à jour le nombre possibilités pour les deux îles en question. Sachant que mise_a_jour_possibilite_ile() s'en charge en parcourant toutes
   les îles, doit-on faire une mise à jour manuelle dans cette fonction ou faire appel à mise_a_jour_possibilite_ile() plusieurs fois dans le main() et au bon moment. */
void Grille::completer_ecart_ile()
{  
	int position_ile_x;
	int position_ile_y;
	int deplacement_ile_x;
	int deplacement_ile_y;
	double valeur;

	for(int i = 0; i < tableau_ile.size(); i++)
	{
		for(int j = 0; j < tableau_ile.size(); j++)
		{
			position_ile_x = tableau_ile[i].get_position_x();
			position_ile_y = tableau_ile[i].get_position_y();
			deplacement_ile_x = tableau_ile[j].get_position_x();
			deplacement_ile_y = tableau_ile[j].get_position_y();

			valeur = sqrt(((deplacement_ile_y - position_ile_y)*(deplacement_ile_y - position_ile_y)) + ((deplacement_ile_x - position_ile_x)*(deplacement_ile_x - position_ile_x)));

			if(valeur == sqrt(2)) // Si la valeur est situé sur les cellules diagonales à la case 
			{
				if(deplacement_ile_y - position_ile_y < 0) //cases en haut
				{
					if(deplacement_ile_x - position_ile_x > 0) //case en haut à droite
					{
						/* Mets les deux cases en noires et crée un ruisseau pour les deux */
						this->grille[position_ile_x + 1][position_ile_y].set_couleur(Cellule::noir);
						this->grille[position_ile_x][position_ile_y - 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_ile_x + 1, position_ile_y);
						creation_element_tableau_ruisseau(position_ile_x, position_ile_y - 1);

					}
					else //case en haut à gauche
					{
						this->grille[position_ile_x - 1][position_ile_y].set_couleur(Cellule::noir);
						this->grille[position_ile_x][position_ile_y - 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_ile_x - 1, position_ile_y);
						creation_element_tableau_ruisseau(position_ile_x, position_ile_y - 1);
					}
				}
				else //bas
				{
					if(deplacement_ile_x - position_ile_x > 0) //droite
					{
						this->grille[position_ile_x + 1][position_ile_y].set_couleur(Cellule::noir);
						this->grille[position_ile_x][position_ile_y + 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_ile_x + 1, position_ile_y);
						creation_element_tableau_ruisseau(position_ile_x, position_ile_y + 1);
					}
					else //gauche
					{
						this->grille[position_ile_x - 1][position_ile_y].set_couleur(Cellule::noir);
						this->grille[position_ile_x][position_ile_y + 1].set_couleur(Cellule::noir);
						creation_element_tableau_ruisseau(position_ile_x - 1, position_ile_y);
						creation_element_tableau_ruisseau(position_ile_x, position_ile_y + 1);
					}
				}
			}

			if(valeur == 2.0) // Dans le cas ou la cellule en question se situe sur les côtés de la case à 2 de distance
			{
				if(deplacement_ile_y - position_ile_y == -2) //haut
				{
					/* Place la case noire entre les deux cellules et crée un ruisseau associé */
					this->grille[position_ile_x][position_ile_y - 1].set_couleur(Cellule::noir);
					creation_element_tableau_ruisseau(position_ile_x, position_ile_y - 1);
				}
				else if(deplacement_ile_y - position_ile_y == 2) //bas
				{
					this->grille[position_ile_x][position_ile_y + 1].set_couleur(Cellule::noir);
					creation_element_tableau_ruisseau(position_ile_x, position_ile_y + 1);
				}
				else if(deplacement_ile_x - position_ile_x == 2) //droite
				{
					this->grille[position_ile_x + 1][position_ile_y].set_couleur(Cellule::noir);
					creation_element_tableau_ruisseau(position_ile_x + 1, position_ile_y);
				}
				else if(deplacement_ile_x - position_ile_x == -2) //gauche
				{
					this->grille[position_ile_x - 1][position_ile_y].set_couleur(Cellule::noir);
					creation_element_tableau_ruisseau(position_ile_x - 1, position_ile_y);
				}
			}
		}
	}
}

void Grille::creation_element_tableau_ruisseau(int x, int y) //permet de créer l'île et en plus de mettre ses attributs aux bonnes valeurs (s'inspirer en cas de problèmes)
{
	int nb_possibilite = 0;
	this->tableau_ruisseau.emplace_back(); //création d'une île noire
	this->tableau_ruisseau.back().set_position_x(x);
	this->tableau_ruisseau.back().set_position_y(y);

	nb_possibilite = calcul_nb_possibilite_ruisseau(this->tableau_ruisseau.back());
	this->tableau_ruisseau.back().set_nb_possibilite_ruisseau(nb_possibilite);
}

int Grille::calcul_nb_possibilite_ruisseau(Ruisseau ruisseau)
{
	int position_x = ruisseau.get_position_x();
	int position_y = ruisseau.get_position_y();
	int nb_possibilite = 0;

	if(position_x + 1 < largeur)
	{
		if(this->grille[position_x + 1][position_y].get_couleur() == Cellule::blanc)
		{
			nb_possibilite++;
		}
	}

	if(position_x - 1 > 0)
	{
		if(this->grille[position_x - 1][position_y].get_couleur() == Cellule::blanc)
		{
			nb_possibilite++;
		}
	}

	if(position_y + 1 < longueur)
	{
		if(this->grille[position_x][position_y + 1].get_couleur() == Cellule::blanc)
		{
			nb_possibilite++;
		}
	}

	if(position_y - 1 > 0)
	{
		if(this->grille[position_x][position_y - 1].get_couleur() == Cellule::blanc)
		{
			nb_possibilite++;
		}
	}

	return nb_possibilite;
}

std::vector<Ile> Grille::mise_a_jour_possibilite_ile(std::vector<Ile> tab_ile, std::vector< std::vector<Cellule> > matrice)
{
	std::cout << "mise à jour" << std::endl;
	int position_x;
	int position_y;
	int position_fils_x, position_fils_y;
	int nb_possibilite = 0;

	for(int i = 0; i < tab_ile.size(); i++)
	{
		tab_ile[i].set_nb_possibilite_ile(0);

		for(int j = 0; j < tab_ile[i].tableau_chemin_ile.size(); j++)
		{
			position_fils_x = tab_ile[i].tableau_chemin_ile[j].get_position_x();
			position_fils_y = tab_ile[i].tableau_chemin_ile[j].get_position_y();

			if(position_fils_x + 1 < largeur)
			{
				if(matrice[position_fils_x + 1][position_fils_y].get_couleur() == Cellule::blanc)
				{
					nb_possibilite++;
				}
			}

			if(position_fils_x - 1 > 0)
			{
				if(matrice[position_fils_x - 1][position_fils_y].get_couleur() == Cellule::blanc)
				{
					nb_possibilite++;
				}
			}

			if(position_fils_y + 1 < longueur)
			{
				if(matrice[position_fils_x][position_fils_y + 1].get_couleur() == Cellule::blanc)
				{
					nb_possibilite++;
				}
			}

			if(position_fils_y - 1 > 0)
			{
				if(matrice[position_fils_x][position_fils_y - 1].get_couleur() == Cellule::blanc)
				{
					nb_possibilite++;
				}
			}

			tab_ile[i].tableau_chemin_ile[j].set_nb_possibilite_cellule(nb_possibilite);
		}

		tab_ile[i].set_nb_possibilite_ile(nb_possibilite);
	}

	for(int i = 0; i < tab_ile.size(); i++)
	{
		position_x = tab_ile[i].get_position_x();
		position_y = tab_ile[i].get_position_y();
		nb_possibilite = 0;

		if(position_x + 1 < largeur)
		{
			if(matrice[position_x + 1][position_y].get_couleur() == Cellule::blanc)
			{
				nb_possibilite++;
			}
		}

		if(position_x - 1 > 0)
		{
			if(matrice[position_x - 1][position_y].get_couleur() == Cellule::blanc)
			{
				nb_possibilite++;
			}
		}

		if(position_y + 1 < longueur)
		{
			if(matrice[position_x][position_y + 1].get_couleur() == Cellule::blanc)
			{
				nb_possibilite++;
			}
		}

		if(position_y - 1 > 0)
		{
			if(matrice[position_x][position_y - 1].get_couleur() == Cellule::blanc)
			{
				nb_possibilite++;
			}
		}

		tab_ile[i].set_nb_possibilite_ile(tab_ile[i].get_nb_possibilite_ile() + nb_possibilite);
	}

	return tab_ile;
}

bool Grille::backtrack(Cellule cellule, std::vector< std::vector<Cellule> > matrice, std::vector<Ile> iles)
{
	//Vérification des placement possible pour l'île

	bool case_droite = false, case_gauche = false, case_haut = false, case_bas = false;
	int position_x, position_y;
	int numero_ile = 0;
	std::vector< std::vector<Cellule> > sauvegarde_matrice(largeur);
	std::vector<Ile> sauvegarde_iles(iles.size());

	std::cout << "cellule_x = " << cellule.get_position_x() << std::endl;
	std::cout << "cellule_y = " << cellule.get_position_y() << std::endl;

	for(int i = 0; i < largeur; i++)
	{
		sauvegarde_matrice[i] = std::vector<Cellule>(longueur);
	}

	for(int i = 0; i < largeur; i++)
	{
		for(int j = 0; j < longueur; j++)
		{
			sauvegarde_matrice[i][j] = matrice[i][j];
		}
	}

	for(int i = 0; i < iles.size(); i++)
	{
		sauvegarde_iles[i] = iles[i];
	}

	// Permet de savoir la position de l'île sur laquelle on travaille, ici numero_ile;
	for(int i = 0; i < tableau_ile.size(); i++)
	{
		if(sauvegarde_iles[i].get_position_x() == cellule.get_position_x() && sauvegarde_iles[i].get_position_y() == cellule.get_position_y())
		{
			numero_ile = i;
		}
		else if(sauvegarde_iles[i].get_position_x() == cellule.get_representant().get_position_x() && sauvegarde_iles[i].get_position_y() == cellule.get_representant().get_position_y())
		{
			numero_ile = i;
		}
	}

	if(sauvegarde_iles[numero_ile].tableau_chemin_ile.size() == 0) // Pas encore de case associée à cette île
	{
		position_x = sauvegarde_iles[numero_ile].get_position_x();
		position_y = sauvegarde_iles[numero_ile].get_position_y();

		if(position_x + 1 < largeur) // Droite
		{
			if(sauvegarde_matrice[position_x + 1][position_y].get_couleur() == Cellule::blanc)
			{
				case_droite = true;
				std::cout << "droite1" << std::endl;
			}
		}

		if(position_x - 1 > 0) // Gauche
		{
			if(sauvegarde_matrice[position_x - 1][position_y].get_couleur() == Cellule::blanc)
			{
				case_gauche = true;
				std::cout << "gauche1" << std::endl;
			}
		}

		if(position_y + 1 < longueur) //bas
		{
			if(sauvegarde_matrice[position_x][position_y + 1].get_couleur() == Cellule::blanc)
			{
				case_bas = true;
				std::cout << "bas1" << std::endl;
			}
		}

		if(position_y - 1 > 0) //haut
		{
			if(sauvegarde_matrice[position_x][position_y - 1].get_couleur() == Cellule::blanc)
			{
				case_haut = true;
				std::cout << "haut1" << std::endl;
			}
		}
	}
	else // Le tableau n'est pas vide, auquel cas on prend la position de la dernière cellule placée
	{
		position_x = sauvegarde_iles[numero_ile].tableau_chemin_ile.back().get_position_x();
		position_y = sauvegarde_iles[numero_ile].tableau_chemin_ile.back().get_position_y();

		if(position_x + 1 < largeur) // Droite
		{
			if(sauvegarde_matrice[position_x + 1][position_y].get_couleur() == Cellule::blanc)
			{
				case_droite = true;
				std::cout << "droite2" << std::endl;
			}
		}

		if(position_x - 1 > 0) // Gauche
		{
			if(sauvegarde_matrice[position_x - 1][position_y].get_couleur() == Cellule::blanc)
			{
				case_gauche = true;
				std::cout << "gauche2" << std::endl;
			}
		}

		if(position_y + 1 < longueur) //bas
		{
			if(sauvegarde_matrice[position_x][position_y + 1].get_couleur() == Cellule::blanc)
			{
				case_bas = true;
				std::cout << "bas2" << std::endl;
			}
		}

		if(position_y - 1 > 0) //haut
		{
			if(sauvegarde_matrice[position_x][position_y - 1].get_couleur() == Cellule::blanc)
			{
				case_haut = true;
				std::cout << "haut2" << std::endl;
			}
		}
	}

	//std::cout << numero_ile << std::endl;
	//std::cout << sauvegarde_iles[numero_ile].get_compteur() << std::endl;

	//Le placement de la prochaine case a plusieurs possibilités
	if(case_haut == true || case_bas == true || case_gauche == true || case_droite == true && sauvegarde_iles[numero_ile].get_compteur() < sauvegarde_iles[numero_ile].get_numero_cellule())
	{
		if(case_haut == true)
		{
			sauvegarde_matrice[position_x][position_y - 1].set_couleur(Cellule::grise); //Mets la case grise
			sauvegarde_matrice[position_x][position_y - 1].set_representant(&sauvegarde_matrice[cellule.get_representant().get_position_x()][cellule.get_representant().get_position_y()]); //Mets le représentant de la case grise à celui de l'île
			sauvegarde_iles[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur() + 1); // Ajoute 1 au compteur de l'île
			std::cout << sauvegarde_iles[numero_ile].get_compteur() << std::endl;
			sauvegarde_iles[numero_ile].tableau_chemin_ile.push_back(sauvegarde_matrice[position_x][position_y - 1]); // Ajoute la cellule grise dans le chemin de l'île
			mise_a_jour_possibilite_cellule(&sauvegarde_matrice[position_x][position_y - 1], sauvegarde_matrice); //Mets à jour les possibilités de placement de la cellule que l'on vient de placer
			sauvegarde_iles = mise_a_jour_possibilite_ile(sauvegarde_iles, sauvegarde_matrice); //mets à jour les possibilités de placement de l'ile
			if(backtrack(sauvegarde_matrice[position_x][position_y - 1], sauvegarde_matrice, sauvegarde_iles) == false)
			{
				for(int i = 0; i < largeur; i++)
				{
					for(int j = 0; j < longueur; j++)
					{
						grille[i][j] = matrice[i][j];
					}
				}

				tableau_ile[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur());
				completer_ecart_ile();
				completer_case();
			}
			else if(backtrack(sauvegarde_matrice[position_x][position_y - 1], sauvegarde_matrice, sauvegarde_iles) == true)
			{
				for(int i = 0; i < largeur; i++)	
				{
					for(int j = 0; j < longueur; j++)
					{
						grille[i][j] = sauvegarde_matrice[i][j];
					}
				}
				
				tableau_ile[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur());
				completer_ecart_ile();
				completer_case();

				/*Relance*/
				backtrack(choix_cellule(), grille, tableau_ile);		
			}
		}
		else if(case_bas == true)
		{
			sauvegarde_matrice[position_x][position_y + 1].set_couleur(Cellule::grise);
			sauvegarde_matrice[position_x][position_y + 1].set_representant(&sauvegarde_matrice[cellule.get_representant().get_position_x()][cellule.get_representant().get_position_y()]);
			sauvegarde_iles[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur() + 1);
			sauvegarde_iles[numero_ile].tableau_chemin_ile.push_back(sauvegarde_matrice[position_x][position_y + 1]);
			sauvegarde_iles = mise_a_jour_possibilite_ile(sauvegarde_iles, sauvegarde_matrice);
			mise_a_jour_possibilite_cellule(&sauvegarde_matrice[position_x][position_y + 1], sauvegarde_matrice);
			if(backtrack(sauvegarde_matrice[position_x][position_y + 1], sauvegarde_matrice, sauvegarde_iles) == false)
			{
				for(int i = 0; i < largeur; i++)
				{
					for(int j = 0; j < longueur; j++)
					{
						grille[i][j] = matrice[i][j];
					}
				}

				tableau_ile[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur());
				completer_ecart_ile();
				completer_case();

				/*Relance*/
			}
			else if(backtrack(sauvegarde_matrice[position_x][position_y + 1], sauvegarde_matrice, sauvegarde_iles) == true)
			{
				for(int i = 0; i < largeur; i++)
				{
					for(int j = 0; j < longueur; j++)
					{
						grille[i][j] = sauvegarde_matrice[i][j];
					}
				}
				
				tableau_ile[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur());
				completer_ecart_ile();
				completer_case();

				/*Relance*/
				backtrack(choix_cellule(), grille, tableau_ile);
			}
		}
		else if(case_droite == true)
		{
			sauvegarde_matrice[position_x + 1][position_y].set_couleur(Cellule::grise);
			sauvegarde_matrice[position_x + 1][position_y].set_representant(&sauvegarde_matrice[cellule.get_representant().get_position_x()][cellule.get_representant().get_position_y()]);
			sauvegarde_iles[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur() + 1);
			sauvegarde_iles[numero_ile].tableau_chemin_ile.push_back(sauvegarde_matrice[position_x + 1][position_y]);
			sauvegarde_iles = mise_a_jour_possibilite_ile(sauvegarde_iles, sauvegarde_matrice);
			mise_a_jour_possibilite_cellule(&sauvegarde_matrice[position_x + 1][position_y], sauvegarde_matrice);
			if(backtrack(sauvegarde_matrice[position_x + 1][position_y], sauvegarde_matrice, sauvegarde_iles) == false)
			{
				for(int i = 0; i < largeur; i++)
				{
					for(int j = 0; j < longueur; j++)
					{
						grille[i][j] = matrice[i][j];
					}
				}

				tableau_ile[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur());
				completer_ecart_ile();
				completer_case();
			}
			else if(backtrack(sauvegarde_matrice[position_x + 1][position_y], sauvegarde_matrice, sauvegarde_iles) == true)
			{
				for(int i = 0; i < largeur; i++)
				{
					for(int j = 0; j < longueur; j++)
					{
						grille[i][j] = sauvegarde_matrice[i][j];
					}
				}

				tableau_ile[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur());
				completer_ecart_ile();
				completer_case();

				/*Relance*/
				std::cout << "relance" << std::endl;
				backtrack(choix_cellule(), grille, tableau_ile);	
			}
		}
		else if(case_gauche == true)
		{
			sauvegarde_matrice[position_x - 1][position_y].set_couleur(Cellule::grise);
			sauvegarde_matrice[position_x - 1][position_y].set_representant(&sauvegarde_matrice[cellule.get_representant().get_position_x()][cellule.get_representant().get_position_y()]);
			sauvegarde_iles[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur() + 1);
			sauvegarde_iles[numero_ile].tableau_chemin_ile.push_back(sauvegarde_matrice[position_x - 1][position_y]);
			sauvegarde_iles = mise_a_jour_possibilite_ile(sauvegarde_iles, sauvegarde_matrice);
			mise_a_jour_possibilite_cellule(&sauvegarde_matrice[position_x - 1][position_y], sauvegarde_matrice);
			if(backtrack(sauvegarde_matrice[position_x - 1][position_y], sauvegarde_matrice, sauvegarde_iles) == false)
			{
				for(int i = 0; i < largeur; i++)
				{
					for(int j = 0; j < longueur; j++)
					{
						grille[i][j] = matrice[i][j];
					}
				}

				tableau_ile[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur());
				completer_ecart_ile();
				completer_case();
			}
			else if(backtrack(sauvegarde_matrice[position_x - 1][position_y], sauvegarde_matrice, sauvegarde_iles) == true)
			{
				for(int i = 0; i < largeur; i++)
				{
					for(int j = 0; j < longueur; j++)
					{
						grille[i][j] = sauvegarde_matrice[i][j];
					}
				}

				tableau_ile[numero_ile].set_compteur(sauvegarde_iles[numero_ile].get_compteur());
				completer_ecart_ile();
				completer_case();

				/*Relance*/
				backtrack(choix_cellule(), grille, tableau_ile);		
			}		
		}
	}

	//Il est impossible de continuer à placer des cases puisqu'il n'y a aucune autre possibilité de placement autour
	else if(case_haut == false && case_bas == false && case_gauche == false && case_droite == false && sauvegarde_iles[numero_ile].get_compteur() < sauvegarde_iles[numero_ile].get_numero_cellule())
	{
		return false;
	}

	//Le placement est terminé, le numéro cellule est remplis et l'île est terminée
	else if(sauvegarde_iles[numero_ile].get_compteur() == sauvegarde_iles[numero_ile].get_numero_cellule())
	{
		return true;
	}

	return true;
}

Cellule Grille::choix_cellule()
{
	int ile = 0, compteur_ile, numero_ile; // Numéro de l'île qui nous intéresse
	std::vector<Ile> substitution_ile(tableau_ile.size());

	for(int i = 0; i < tableau_ile.size(); i++)
	{
		substitution_ile[i] = tableau_ile[i];
	}

	for(int i = 0; i < substitution_ile.size(); i++)
	{
		if(substitution_ile[i].get_compteur() == substitution_ile[i].get_numero_cellule())
		{
			substitution_ile.erase(substitution_ile.begin() + i);
		}
	}

	compteur_ile = substitution_ile[0].get_compteur();
	numero_ile = substitution_ile[0].get_numero_cellule();

	for(int i = 1; i < substitution_ile.size(); i++)
	{
		if(substitution_ile[i].get_numero_cellule() <= numero_ile)
		{
			if(substitution_ile[i].get_compteur() <= compteur_ile)
			{
				ile = i;
				compteur_ile = substitution_ile[i].get_compteur();
				numero_ile = substitution_ile[i].get_numero_cellule();
			}
		}
	}

	int position_x = substitution_ile[ile].get_position_x();
	int position_y = substitution_ile[ile].get_position_y();

	std::cout << "---------------------------ile_x = " << position_x << std::endl;
	std::cout << "---------------------------ile_y = " << position_y << std::endl;

	return grille[position_x][position_y];
}

void Grille::mise_a_jour_possibilite_cellule(Cellule* cellule, std::vector< std::vector<Cellule> > sauvegarde_matrice)
{
	int position_x = cellule->get_position_x();
	int position_y = cellule->get_position_y();
	int nb_possibilite = 0;

	if(position_x + 1 < largeur)
	{
		if(sauvegarde_matrice[position_x + 1][position_y].get_couleur() == Cellule::blanc)
		{
			nb_possibilite++;
		}
	}

	if(position_x - 1 > 0)
	{
		if(sauvegarde_matrice[position_x - 1][position_y].get_couleur() == Cellule::blanc)
		{
			nb_possibilite++;
		}
	}

	if(position_y + 1 < longueur)
	{
		if(sauvegarde_matrice[position_x][position_y + 1].get_couleur() == Cellule::blanc)
		{
			nb_possibilite++;
		}
	}

	if(position_y - 1 > 0)
	{
		if(sauvegarde_matrice[position_x][position_y - 1].get_couleur() == Cellule::blanc)
		{
			nb_possibilite++;
		}
	}
	cellule->set_nb_possibilite_cellule(nb_possibilite);
}

int Grille::get_largeur(){return largeur;}
int Grille::get_longueur(){return longueur;}
void Grille::set_longueur(int lo){longueur = lo;}
void Grille::set_largeur(int la){largeur = la;}