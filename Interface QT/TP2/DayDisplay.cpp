#include "DayDisplay.h"
#include <QBoxLayout>
#include <QPaintEvent>
#include <QPainter>
#include <iostream>
#include <QRectF>
#include <QTextOption>
#include <QScrollBar>



using namespace std;

//Constructeur du Widget paramétré avec la date du jour
DayDisplay::DayDisplay(QDate Date_Jour, QWidget *parent ) : QWidget (parent), m_Date_Jour(Date_Jour)
{
    //Création d'un QString de Date selon un format "Jour numéro Mois Année"
    TEXT_Date = m_Date_Jour.toString(QString("dddd d MMMM  yyyy"));
}

//Constructeur du Widget paramétré avec la date du jour -> INTITIALIZER LIST
DayDisplay::DayDisplay(QDate Date_Jour, vector<IcsEvent> VCT_Cours , QWidget *parent ,QGraphicsView *View) : QWidget (parent) , m_Date_Jour(Date_Jour), m_VCT_Cours(VCT_Cours)
{
    //Création d'un QString de Date selon un format "Jour numéro Mois Année"
    TEXT_Date = m_Date_Jour.toString(QString("dddd d MMMM  yyyy"));
}


void DayDisplay::paintEvent(QPaintEvent * /*PaintEvent*/)
{
    QPainter Painter(this);
    this->setFixedSize(1400,600);

    //Création de la charte Graphique :
    QColor COLOR_Bleu = QColor(49, 140, 231);
    QColor COLOR_Noir = QColor(0 , 0 , 0);
    QColor COLOR_VertTP = QColor(165, 255, 42);
    QColor COLOR_VioletCM = QColor(191 , 189 , 255);
    QColor COLOR_BleuTD = QColor(134 , 185 , 255);
    QColor COLOR_Gris = QColor(188 , 187 , 187);

    int W = 200;
    int H = 500 ;

    Painter.setPen(QPen(COLOR_Noir , 1.5));

    //Rectangle Contour
    Painter.setBrush(QBrush (QColor(255, 255, 255), Qt::SolidPattern));
    QRect Rect_Contour = QRect(0 , 0 , W , H); //Création d'un contour
    Painter.drawRect(Rect_Contour); //Grand Rectangle contour

    Painter.setWindow(Rect_Contour);
    Painter.setViewport(Rect_Contour);

    //Rectangle Haut - DATE
    Painter.setBrush(QBrush (COLOR_Bleu, Qt::SolidPattern));
    QRect Rect_DATE = QRect(0 , 0 , W , 35); //Création d'un
    Painter.drawRect(Rect_DATE);
    Painter.setPen(QPen(QColor(255, 255 , 255))); //Couleur Blanche

    //Impression de la date sur dans le calendrier
    Painter.drawText(Rect_DATE , Qt::AlignCenter , TEXT_Date); //Dessin du texte

    int heure = 8; //Premiere information d'heure
    Painter.setFont(QFont("Arial", 9));

    //Dessin des lignes bleues continues et des heures
    for (int offset1 = 50 , i = 0 ; i < 12 ;  offset1 += 40, ++i )
    {
        //Dessin des lignes séparatrice des heure - Couleur BLEUE
        Painter.setPen(QPen(COLOR_Bleu , 1)); //Couleur Bleue
        Painter.drawLine(0 , offset1 , W , offset1); //Dessin de la ligne

        Painter.setBrush(QBrush (QColor(255, 255, 255), Qt::SolidPattern));
        QRect Rect_Heure = QRect(7 , offset1-6 , 25 , 12); //Création d'un
        Painter.drawRoundedRect(Rect_Heure, 60, 60); //Dessin des rectangles autour des heures

        //Fabrication et écriture des informations horraires - Couleur NOIRE
        Painter.setPen(QPen(QColor(0, 0, 0))); //Couleur Noire
        QString heure_TXT = QString::number(heure) + "H"; //Fabrication de la chaine de caractère
        Painter.drawText(Rect_Heure , Qt::AlignCenter , heure_TXT); //Dessin du texte

        heure++; //Incrémentation de l'heure
    }

    //Dessin des lignes bleus en pointillés
    for (int offset2 = 70 ; offset2 < H ; offset2 += 40 )
    {
        QPen Pointille = QPen (COLOR_Bleu , 1);
        Pointille.setStyle(Qt::DotLine);
        Painter.setPen(Pointille);
        Painter.drawLine(0 , offset2 , W , offset2); //Dessin de la ligne
    }


    //------------------------------------
    // Récupération et Dessin des cours
    //------------------------------------

    for (ulong i = 0 ; i < m_VCT_Cours.size() ; i++)
    {
        //Récupération des informations
        EVT_Summary = m_VCT_Cours[i].what();
        EVT_Prof = m_VCT_Cours[i].prof();
        EVT_Salle = m_VCT_Cours[i].where();

        //Heures de début et de fin
        EVT_Start = m_VCT_Cours[i].start();
        EVT_Stop = m_VCT_Cours[i].stop();

        //Calcul de la durée :
        EVT_Duree = EVT_Start.secsTo(EVT_Stop);
        EVT_Debut_Heure = EVT_Start.hour();
        EVT_Debut_Minute = EVT_Start.minute();

        decalage = 50 + 40*(EVT_Debut_Heure-8) + EVT_Debut_Minute*40/60; //Calcul du Décalage
        longueur = EVT_Duree*40/3600; //Calcul de la longueur


        Painter.setPen(QPen(COLOR_Noir , 1));

        //Affectation de la couleur de fond en fonction du type de cours
        if (EVT_Summary.contains("TP")) {Painter.setBrush(QBrush (COLOR_VertTP, Qt::SolidPattern));}
        else if (EVT_Summary.contains("CM")) {Painter.setBrush(QBrush (COLOR_VioletCM, Qt::SolidPattern));}
        else if (EVT_Summary.contains("TD")) {Painter.setBrush(QBrush (COLOR_BleuTD, Qt::SolidPattern));}
        else {Painter.setBrush(QBrush (COLOR_Gris, Qt::SolidPattern));}

        QRectF Rect_Cours = QRectF(40 , decalage , W-45 , longueur); //Création d'un rectangle de cours
        Painter.drawRoundedRect(Rect_Cours, 10 , 10); //Arrondissement des angles

        //Ecriture du texte :
        Painter.setPen(QPen(COLOR_Noir));
        Painter.setFont(QFont("Arial", 7));
        QTextOption Option(Qt::AlignCenter);
        Option.setWrapMode(QTextOption::WordWrap);
        Painter.drawText(Rect_Cours , EVT_Summary + "\n\r"+ EVT_Salle + "\n\r" + EVT_Prof , Option); //Dessin du texte
    }


    Painter.end();


}


DayDisplay::~DayDisplay() {}
