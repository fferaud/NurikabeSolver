#ifndef MAFENETRE_H
#define MAFENETRE_H

#include <QWidget>
#include <QLabel>
#include <QTabWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QSlider>
#include <QMessageBox>
#include <QString>
#include <QPainter>
#include "Cellule.h"
#include "Grille.h"
#include "Ile.h"

class MaFenetre : public QWidget
{
    Q_OBJECT
public:
    MaFenetre();
    void affiche_grilleQt(int, int, Grille);

signals:

public slots:
    void ChangeQLabel();
    void MessErrorGen();
    void MessErrorSolv();


private:
    QTabWidget *onglets;
    QWidget *page1;
    QWidget *page2;
    QWidget *page3;

    //page 1
    QLineEdit *lineEdit;
    QPushButton *BouValPseudo;
    QLabel *IntroAppli;
    QLabel *InfoAccueil;


    QVBoxLayout *vbox1;

    //page 2
    QLabel *IntroGeneration;
    QPushButton *BouGeneration;

    QVBoxLayout *vbox2;

    //page 3
    QLabel *ImageDemo;
    QPushButton *BouSolver;

    QVBoxLayout *vbox3;

    //Nurikabe
    QLabel *RectFond;

};

#endif // MAFENETRE_H
