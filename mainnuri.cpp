
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QtWidgets>
#include "MaFenetre.h"

#include <vector>
#include <string>
#include <stdio.h>
#include <time.h>


//*** Fonction pour faire une pause ***//
void sleepcp(int milliseconds)
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    MaFenetre fenetre;
    int const n=3;
    int const m=3;
    int const longueur_grille = 5; // y
    int const largeur_grille = 8; // x

    //*** Valeurs de test de la fenetre ***//
    int** Tab = new int*[n];

    for (int i=0;i<n;i++)
    {
        Tab[i]=new int[m];
    }

    Tab[0][0]=0;
    Tab[0][1]=0;
    Tab[0][2]=1;
    Tab[1][0]=0;
    Tab[1][1]=1;
    Tab[1][2]=1;
    Tab[2][0]=0;
    Tab[2][1]=1;
    Tab[2][2]=0;

    //*** Fin valeurs de test ***//

    /* Création de la grille */

    Grille plateau(largeur_grille, longueur_grille);
    Ile ile1(2,2,2);
    Ile ile2(2,0,3);
    Ile ile3(5,3,1);
    Ile ile4(1,3,4);
    Ile ile5(3,4,2);
    Ile ile6(7,4,3);
    Ile ile7(5,1,4);
    plateau.tableau_ile.push_back(ile1);
    plateau.tableau_ile.push_back(ile2);
    plateau.tableau_ile.push_back(ile3);
    plateau.tableau_ile.push_back(ile4);
    plateau.tableau_ile.push_back(ile5);
    plateau.tableau_ile.push_back(ile6);
    plateau.tableau_ile.push_back(ile7);

    /* Varabiables */

    plateau.grille[2][2].set_couleur(Cellule::ile);
    plateau.grille[2][0].set_couleur(Cellule::ile);
    plateau.grille[5][3].set_couleur(Cellule::ile);
    plateau.grille[1][3].set_couleur(Cellule::ile);
    plateau.grille[3][4].set_couleur(Cellule::ile);
    plateau.grille[7][4].set_couleur(Cellule::ile);
    plateau.grille[5][1].set_couleur(Cellule::ile);

    //*** Ce sera à lancer quand on appuyera sur le bouton de resolution ***//
    plateau.completer_ecart_ile();
    plateau.tableau_ile = plateau.mise_a_jour_possibilite_ile(plateau.tableau_ile, plateau.grille);
    plateau.completer_case();
    plateau.tableau_ile = plateau.mise_a_jour_possibilite_ile(plateau.tableau_ile, plateau.grille);
    plateau.backtrack(plateau.choix_cellule(), plateau.grille, plateau.tableau_ile);

    //*** A lancer à chaque changement d'une Cellule dans la grille
    fenetre.affiche_grilleQt(plateau.get_largeur() ,plateau.get_longueur(), plateau);


    fenetre.show();

    //*** Ce sera à placer au moment ou le programme doit d'arreter ***//
    /*for(int i = 0; i < largeur_grille; i++)
    {
        plateau.grille[i].clear();
    }
    plateau.grille.clear();
    plateau.tableau_ile.clear();
    plateau.tableau_ruisseau.clear();*/


    return app.exec();

    //*** Comment faire une pause ***//
    /*std::cout << "Hi! At the count to 3, I'll die! :)" << std::endl;
    sleepcp(3000);
    std::cout << "urrrrggghhhh!" << std::endl;*/


}
