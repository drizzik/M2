#ifndef WIDGET_JOUR_H
#define WIDGET_JOUR_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QDate>
#include <QGraphicsView>

#include "IcsEvent.h"

class DayDisplay : public QWidget
{
    Q_OBJECT

private :
    QDate Date_Jour;
    QDate m_Date_Jour;

    vector<IcsEvent> VCT_Cours;
    vector<IcsEvent> m_VCT_Cours;

    QString *heure_TXT;
    QString TEXT_Date;
    QString EVT_Date;
    QString EVT_Summary;
    QString EVT_Prof;
    QString EVT_Salle;
    QString TXT_Cours;

    QTime EVT_Start;
    QTime EVT_Stop;

    int EVT_Duree;
    int EVT_Debut_Heure;
    int EVT_Debut_Minute;
    int decalage;
    int longueur;



public:
    DayDisplay(QDate Date_Jour, QWidget *parent = nullptr);

    DayDisplay(QDate Date_Jour, vector<IcsEvent> VCT_Cours, QWidget *parent = nullptr,QGraphicsView *View = nullptr);


    virtual void paintEvent (QPaintEvent *); //Fonction virtuelle

    ~DayDisplay();
};

#endif // WIDGET_JOUR_H


