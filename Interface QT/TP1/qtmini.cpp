#include "qtmini.h"
#include <iostream>
#include <QTimer>


QtMini::QtMini() : QMainWindow(nullptr)
{
    //Initialisation et création de la grille
    QWidget *g = new QWidget(this);             //création du widget principal
    QGridLayout *gl = new QGridLayout;          //Création de la grille
    gl->setSpacing(4);                          //mise an place de l'espacement à 4
    g->setLayout(gl);                           //Définir le layout du widget principal

    //Groupe Boutton
    QGroupBox *gbPushBtn = new QGroupBox("QPushButton");            //création du QGroupBox
    gl->addWidget(gbPushBtn,1,0,1,1);                               //Ajout à la grille
    QPushButton *qPushBtn = new QPushButton("Test",nullptr);        //Création du QPushButton
    QVBoxLayout *vbox = new QVBoxLayout;                            //Création du QVBoxLayout
    vbox->addWidget(qPushBtn);                                      //Ajout du bouton a la Vbox
    gbPushBtn->setLayout(vbox);                                     //Définition du Layout de la groupBox avec la vbox
    //Label Boutton
    labelBtn = new QLabel("Label btn");                             //Création du QLabel
    gl->addWidget(labelBtn,1,1,1,1);                                //Ajout à la grille
    //----connect----
    connect(qPushBtn,SIGNAL(pressed()),this,SLOT(btnPressed()));    //Connect quand le bouton est appuyé (appel de fct1)
    connect(qPushBtn,SIGNAL(released()),this,SLOT(btnReleased()));  //Connect quand le bouton est relaché (appel de fct2)
    //---Fin Groupe Boutton---


    //Groupe Slider
    QGroupBox *gbSlider = new QGroupBox("QSlider");
    gl->addWidget(gbSlider,2,0,1,1);
    QSlider *qSlider = new QSlider(Qt::Horizontal,nullptr);         //Création du Slider
    qSlider->setMaximum(100);                                       //Mise en place du minimum et maximum
    qSlider->setMinimum(0);
    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(qSlider);
    gbSlider->setLayout(vbox2);
    //Label Slider
    lineSlider = new QLineEdit("VALEUR SLIDER");                    //Création de la QLineEdit
    gl->addWidget(lineSlider,2,1,1,1);
    //----connect----
    connect(qSlider,SIGNAL(valueChanged(int)),this,SLOT(changeValue(int))); //Connect et appel de fonction avec envoie
    //---Fin Groupe Slider---                                               // de la valeur du slider


    //Groupe Radio Boutton
    QGroupBox *gbRadioBtn = new QGroupBox("QRadioButton");
    gl->addWidget(gbRadioBtn,3,0,1,1);
    QRadioButton *qRadioButton = new QRadioButton("Café",nullptr);          //Création du premier QRadioButton
    QRadioButton *qRadioButton2 = new QRadioButton("Chocolat",nullptr);     //Création du second QRadioButton
    QVBoxLayout *vbox3 = new QVBoxLayout;
    vbox3->addWidget(qRadioButton);
    vbox3->addWidget(qRadioButton2);
    gbRadioBtn->setLayout(vbox3);
    //Label Radio Boutton
    lineRadio = new QLabel("Café ou choco ?");
    gl->addWidget(lineRadio,3,1,1,1);
    //----connect----
    connect(qRadioButton,SIGNAL(clicked()),this,SLOT(onRb1Clicked()));      //Appelle des fonctions
    connect(qRadioButton2,SIGNAL(clicked()),this,SLOT(onRb2Clicked()));
    //---Fin Groupe Radio Boutton---


    //Groupe Color Dialog
    QGroupBox *gbColorDialog = new QGroupBox("QColorDialog");
    gl->addWidget(gbColorDialog,4,0,1,1);
    QPushButton *qPushBtnColor = new QPushButton("Choisissez une couleur...",nullptr);
    QVBoxLayout *vbox4 = new QVBoxLayout;
    vbox4->addWidget(qPushBtnColor);
    gbColorDialog->setLayout(vbox4);
    //Label Color Dialog
    textDialog = new QTextEdit("ColorDialog");
    gl->addWidget(textDialog,4,1,1,1);
    //----connect----
    connect(qPushBtnColor,SIGNAL(clicked()),this,SLOT(setBackgroundColor()));
    //---Fin Groupe Color Dialog---


    //Groupe Combo Box
    QGroupBox *gbComboBox = new QGroupBox("QComboBox");
    gl->addWidget(gbComboBox,5,0,1,1);
    QComboBox *qComboBox = new QComboBox(nullptr);      //Création de la QComboBox
    for(int i = 0; i < 10; i++)
    {
        qComboBox->addItem(QString::number(i));         //Remplissage de la QComboBox
    }
    QVBoxLayout *vbox5 = new QVBoxLayout;
    vbox5->addWidget(qComboBox);
    gbComboBox->setLayout(vbox5);
    //Label Combo Box
    textCombo = new QTextEdit("Nombre ?");
    gl->addWidget(textCombo,5,1,1,1);
    //---connect---
    connect(qComboBox,SIGNAL(activated(int)),this,SLOT(displayChoice(int))); //Connect et appel de fonction
    //---Fin Groupe Combo Box---

    //Groupe TabBar
    QTabBar *qTabBar = new QTabBar(this);
    qTabBar->addTab("tab 1");               //Création des tabs
    qTabBar->addTab("tab 2");
    gl->addWidget(qTabBar,0,0,1,1);
    //---Fin Groupe TabBar---


    //Groupe ProgressBar
    qProgressBar = new QProgressBar(nullptr);       //Création de la QProgressBar
    gl->addWidget(qProgressBar,6,0,2,1);            //Ajout dans la grille
    QTimer *timer = new QTimer(this);               //Création du Timer
    connect(timer, SIGNAL(timeout()), this, SLOT(updateProgress()));
    timer->start(1000);                             //Démarre et redémarre le Timer toutes les secondes
    //---Fin Groupe ProgressBar---

     setCentralWidget(g);
}

//Fonctions appelées par les connects

void QtMini::btnPressed()
{
    labelBtn->setText("appuyé");            //Change le texte du QLabel
}
void QtMini::btnReleased()
{
    labelBtn->setText("relaché");           //Change le texte du QLabel
}
void QtMini::changeValue(int value)
{
    lineSlider->setText(QString::number(value)); //Met en texte(string) le nombre reçu
}
void QtMini::onRb1Clicked()
{
    lineRadio->setText("Café");
}
void QtMini::onRb2Clicked()
{
    lineRadio->setText("Chocolat");
}
void QtMini::setBackgroundColor()
{
    QColor color = QColorDialog::getColor(Qt::yellow, this ); //Crée une couleur est la sélectionne avec l'interface
    QPalette p = textDialog->palette();                       //Crée une  palette
    p.setColor(QPalette::Base, color);                        //
    textDialog->setPalette(p);                                //Change la couleur du QTextDialog

}
void QtMini::displayChoice(int value)
{
    textCombo->setText(QString::number(value));
}
void QtMini::updateProgress()
{
    qProgressBar->setValue(qProgressBar->value()+1);        //Incrémente la valeur de la QProgressBar a chaque appel
}
