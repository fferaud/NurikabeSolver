// MaFenetre.cpp

#include "MaFenetre.h"

MaFenetre::MaFenetre() : QWidget()
{
    setFixedSize(950, 400);

    onglets = new QTabWidget(this);
    onglets->setGeometry(30, 20, 350, 350);

    // Création des pages, en utilisant un widget parent pour contenir chacune des pages
    page1 = new QWidget;
    page2 = new QWidget;
    page3 = new QWidget;


    // Création du contenu des pages de widgets

        // Page 1


        lineEdit = new QLineEdit("Choisir un nom");
        BouValPseudo = new QPushButton("Valider");
        IntroAppli = new QLabel("Bienvenue dans notre logiciel de résolution et de génération de grille pour le jeu du Nurikabe");
        IntroAppli->setWordWrap(true);
        InfoAccueil = new QLabel("Note : Voici les fonctionnalités qui vont être developpées dans notre logiciel.\nLes fonctions ne fonctionnent pas encore, elles vont être ajoutées sous peu et l'ergonomie va être retravaillée. Cet environnement permet actuellement de tester ce qu'il est possible de faire avec Qt.");
        InfoAccueil->setWordWrap(true);


        vbox1 = new QVBoxLayout;
        vbox1->addWidget(lineEdit);
        vbox1->addWidget(BouValPseudo);
        vbox1->addWidget(IntroAppli);
        vbox1->addWidget(InfoAccueil);

        page1->setLayout(vbox1);

        // Page 2

        BouGeneration = new QPushButton("Générer une grille");
        IntroGeneration = new QLabel("Vous êtes dans l'onglet de génération de grille de Nurikabe,appuyez sur le bouton pour lancer la génération.");
        IntroGeneration->setWordWrap(true);

        vbox2 = new QVBoxLayout;
        vbox2->addWidget(IntroGeneration);
        vbox2->addWidget(BouGeneration);

        page2->setLayout(vbox2);

        // Page 3
        ImageDemo = new QLabel();
        ImageDemo->setPixmap((QPixmap("grille.png")).scaled(250,250));
        ImageDemo->setAlignment(Qt::AlignCenter);

        BouSolver = new QPushButton("Résoudre la grille");

        vbox3 = new QVBoxLayout;
        vbox3->addWidget(ImageDemo);
        vbox3->addWidget(BouSolver);

        page3->setLayout(vbox3);




    // Ajout des onglets au QTabWidget, en indiquant la page qu'ils contiennent
    onglets->addTab(page1, "Accueil");
    onglets->addTab(page2, "Générateur de grille");
    onglets->addTab(page3, "Solveur du Nurikabe");



    QObject::connect(BouValPseudo, SIGNAL(clicked()), this, SLOT(ChangeQLabel()));
    QObject::connect(BouGeneration, SIGNAL(clicked()), this, SLOT(MessErrorGen()));
    QObject::connect(BouSolver, SIGNAL(clicked()), this, SLOT(MessErrorSolv()));
}

//*** Slots ***//
void MaFenetre::ChangeQLabel()
{
    QString pseudo = lineEdit->text();
    if (!pseudo.isEmpty())
    {
        IntroAppli->setText((pseudo+", bienvenue dans notre logiciel de résolution et de génération de grille pour le jeu du Nurikabe"));
    }
}

void MaFenetre::MessErrorGen()
{
    QMessageBox::critical(this, "Erreur génération de grille", "L'implémentation de la génération de la grille arrive sous peu. \nRevenez plus tard ;) ");
}

void MaFenetre::MessErrorSolv()
{
    QMessageBox::critical(this, "Erreur Solveur", "L'implémentation de la résolution de la grille arrive sous peu. \nRevenez plus tard ;)");
}

//*** Méthode public ***//
void MaFenetre::affiche_grilleQt(int nb_col, int nb_ligne, Grille plateau)
{
    RectFond = new QLabel(this);
    RectFond->setPixmap((QPixmap("noir.png")).scaled(33*nb_col+1,33*nb_ligne+1));
    RectFond->move(450, 20);

    QLabel* TabQ[nb_col][nb_ligne];
    for (int k=0; k<nb_col; k++)
    {
        for(int i=0; i<nb_ligne; i++)
        {
            TabQ[k][i]= new QLabel(this);
        }
    }

    int posX=451;
    for (int i=0; i<nb_col ; i++)
    {
        int posY=21;
        for(int j=0; j<nb_ligne ;j++)
        {
            if (plateau.grille[i][j].get_couleur() == Cellule::noir)
                TabQ[i][j]->setPixmap(QPixmap("noir.png"));
            else if (plateau.grille[i][j].get_couleur() == Cellule::blanc)
                TabQ[i][j]->setPixmap(QPixmap("blanc.png"));
            else if (plateau.grille[i][j].get_couleur() == Cellule::grise)
                TabQ[i][j]->setPixmap(QPixmap("gris.png"));
            else if (plateau.grille[i][j].get_couleur() == Cellule::ile)
                TabQ[i][j]->setPixmap(QPixmap("gris.png"));
            else if (plateau.grille[i][j].get_couleur() == Cellule::ruisseau)
                TabQ[i][j]->setPixmap(QPixmap("noir.png"));
            else
            {
                std::cout<<"I don't know"<<std::endl;
                TabQ[i][j]->setPixmap(QPixmap("blanc.png"));
            }
            TabQ[i][j]->move(posX, posY);
            posY+=33;

        }
        posX+=33;
    }


}
