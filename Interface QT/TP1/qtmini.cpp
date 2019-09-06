#include "qtmini.h"
#include <iostream>

QtMini::QtMini() : QMainWindow(nullptr)
{
    //Initialisation et création de la grille
    QWidget *g = new QWidget(this);
    QGridLayout *gl = new QGridLayout;
    gl->setSpacing(4);
    g->setLayout(gl);

    //Groupe Boutton
    QGroupBox *gbPushBtn = new QGroupBox("QPushButton");
    gl->addWidget(gbPushBtn,1,0,1,1);
    QPushButton *qPushBtn = new QPushButton("Test",nullptr);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(qPushBtn);
    gbPushBtn->setLayout(vbox);
    //Label Boutton
    labelBtn = new QLabel("Label btn");
    gl->addWidget(labelBtn,1,1,1,1);
    //----connect----
    connect(qPushBtn,SIGNAL(pressed()),this,SLOT(btnPressed()));
    connect(qPushBtn,SIGNAL(released()),this,SLOT(btnReleased()));
    //---Fin Groupe Boutton---


    //Groupe Slider
    QGroupBox *gbSlider = new QGroupBox("QSlider");
    gl->addWidget(gbSlider,2,0,1,1);
    QSlider *qSlider = new QSlider(Qt::Horizontal,nullptr);
    qSlider->setMaximum(100);
    qSlider->setMinimum(0);
    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(qSlider);
    gbSlider->setLayout(vbox2);
    //Label Slider
    lineSlider = new QLineEdit("VALEUR SLIDER");
    gl->addWidget(lineSlider,2,1,1,1);
    //----connect----
    connect(qSlider,SIGNAL(valueChanged(int)),this,SLOT(changeValue(int)));
    //---Fin Groupe Slider---


    //Groupe Radio Boutton
    QGroupBox *gbRadioBtn = new QGroupBox("QRadioButton");
    gl->addWidget(gbRadioBtn,3,0,1,1);
    QRadioButton *qRadioButton = new QRadioButton("Café",nullptr);
    QRadioButton *qRadioButton2 = new QRadioButton("Chocolat",nullptr);
    QVBoxLayout *vbox3 = new QVBoxLayout;
    vbox3->addWidget(qRadioButton);
    vbox3->addWidget(qRadioButton2);
    gbRadioBtn->setLayout(vbox3);
    //Label Radio Boutton
    lineRadio = new QLabel("Café ou choco ?");
    gl->addWidget(lineRadio,3,1,1,1);
    //----connect----
    connect(qRadioButton,SIGNAL(clicked()),this,SLOT(onRb1Clicked()));
    connect(qRadioButton2,SIGNAL(clicked()),this,SLOT(onRb2Clicked()));
    //---Fin Groupe Radio Boutton---


    //Groupe Color Dialog
    QGroupBox *gbColorDialog = new QGroupBox("QColorDialog");
    gl->addWidget(gbColorDialog,4,0,1,1);
    qcdialog = new QColorDialog();
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
    QComboBox *qComboBox = new QComboBox(nullptr);
    for(int i = 0; i < 10; i++)
    {
        qComboBox->addItem(QString::number(i));
    }
    QVBoxLayout *vbox5 = new QVBoxLayout;
    vbox5->addWidget(qComboBox);
    gbComboBox->setLayout(vbox5);
    //Label Combo Box
    textCombo = new QTextEdit("Nombre ?");
    gl->addWidget(textCombo,5,1,1,1);
    //---connect---
    connect(qComboBox,SIGNAL(activated(int)),this,SLOT(displayChoice(int)));
    //---Fin Groupe Combo Box---

    //Groupe TabBar
    QTabBar *qTabBar = new QTabBar(this);
    qTabBar->addTab("tab 1");
    qTabBar->addTab("tab 2");
    //---Fin Groupe TabBar---


    setCentralWidget(g);
}

//Fonctions appelées par les connects

void QtMini::btnPressed()
{
    labelBtn->setText("appuyé");
}
void QtMini::btnReleased()
{
    labelBtn->setText("relaché");
}
void QtMini::changeValue(int value)
{
    lineSlider->setText(QString::number(value));
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
    QColor color = QColorDialog::getColor(Qt::yellow, this );
    QPalette p = textDialog->palette();
    p.setColor(QPalette::Base, color);
    textDialog->setPalette(p);

}
void QtMini::displayChoice(int value)
{
    textCombo->setText(QString::number(value));
}
