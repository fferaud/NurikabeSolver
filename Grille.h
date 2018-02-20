#ifndef GRILLE_H
#define GRILLE_H
#include <iostream>
#include <string>
#include <vector>
#include "Cellule.h"
#include "Ile.h"
#include "Ruisseau.h"

class Grille
{
	public:
		std::vector< std::vector<Cellule> > grille; //Dans le cas d'une grille de taille variable
		std::vector<Ile> tableau_ile; //Tableau pointant sur toutes les iles de la grille.
		std::vector<Ruisseau> tableau_ruisseau; //Tableau pointant sur tous les ruisseaux de la grille

		/* Méthodes */
		Grille();
		Grille(int, int);
		void completer_case(); // Place les cases noirs autour des îles à 1 et compléte si il ne reste qu'une seule possibilitée
		void completer_case_2(Ile); // Place les cases noirs autours des îles à 2 en diagonales si les conditions sont respectées.
		void completer_ecart_ile(); // Complete avec des cases noires les îles espacées de 1 à 2 cases selon la règle
		void max_distance_ile(Ile); // Place des cases noirs si elles sont hors de portées de toutes les îles
		void regle_carre_noir(); // Si trois cases noires sont côte à côte de manière triangulaire, mets la quatrième blanche
		bool connectivite_noir(); // Place une case noir de manière logique et obligatoire sur une rivière lorsqu'il a une seule possibilité au niveau du ruisseau.
		bool backtrack(Cellule, std::vector< std::vector<Cellule> >, std::vector<Ile>); // Choix de placer un blanc puis vérification.
		void creation_element_tableau_ruisseau(int, int); //crée un objet dans tableau_ruisseau et modifie ses attribues x et y
		int calcul_nb_possibilite_ruisseau(Ruisseau); // Mets à jour le nb de possibilités disponible pour un ruisseau donné
		std::vector<Ile> mise_a_jour_possibilite_ile(std::vector<Ile>, std::vector< std::vector<Cellule> >); // Mets à jour le nb de possibilités pour toutes les iles
		Cellule choix_cellule(); // Renvoi le numéro de l'île avec le moins de cases à placer dans le tableau_ile
		void mise_a_jour_possibilite_cellule(Cellule*, std::vector< std::vector<Cellule> >); // Mets à jour les possibilités d'une cellule donnée
		int get_largeur();
		int get_longueur();
		void set_longueur(int);
		void set_largeur(int);
	private:
		int largeur;
		int longueur;
		
};

#endif

//backtrack

/* Commencer sur l'île la plus petite avec 2 réponses maxi pour commencer */