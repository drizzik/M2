#include "mainwindow.h"
#include "TimeTable.h"
#include <DayDisplay.h>

#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsProxyWidget>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QSize>
#include <QPainter>
#include <QPushButton>
#include <QGraphicsItem>
#include <QScrollBar>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>


#include <iostream>
using namespace std;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //Lien vers le dossier :
    QString Chemin = "/Codage/interface QT/TP2";

    //Initialisation

    QDate Date_Today = QDate::currentDate();
    NUM_Semaine = Date_Today.weekNumber();




    //Création d'un slider
    Slider_Semaine = new QSlider(Qt::Horizontal);
    Slider_Semaine->setMaximum(52);
    Slider_Semaine->setMinimum(1);
    Slider_Semaine->setValue(NUM_Semaine);

    //Création des boutons
    Bouton1 = new QPushButton;
    Bouton1->setIcon(QIcon(Chemin + "/ICONE-STOP.png"));
    Bouton1->setFixedSize(50,50);

    Bouton2 = new QPushButton();
    Bouton2->setIcon(QIcon(Chemin + "/ICONE-Cal.png"));
    Bouton2->setFixedSize(50,50);

    //Création d'une zone de texte pour y afficher le numero de semaine
    Text_Semaine = new QLineEdit(this);
    Text_Semaine->setReadOnly(true);
    Text_Semaine->setFixedSize(50,30);
    Text_Semaine->setText(QString::number(NUM_Semaine, 'i', 0));

    //Connect des boutons
    connect(Slider_Semaine , SIGNAL(valueChanged(int)) , this, SLOT (ModificationSemaine(int)) );
    connect(Bouton1 , SIGNAL(clicked()) , this , SLOT(End()) );
    connect(Bouton2 , SIGNAL(clicked()) , this , SLOT(MoveToToday()) );



    //——————————————————————————————————————————————————
    //   -- Création d'un slider de déplacement
    //——————————————————————————————————————————————————

    TimeTable EDT;

    //Création d'une scène et d'une view
    Scene = new QGraphicsScene(this);
    Scene->setSceneRect(0,0,400*200,H);

    //Importation du fichier ICS -> Vérifie si le fichier existe
    try {EDT.loadFile(Chemin + "/Edt.ics");}
    catch(const char* error) {cout << error;} //Sinon, affiche le message d'erreur prévu dans la classe TimeTable

    vector<QDate> Vecteur_JoursCours; //Vecteur de Dates
    vector<IcsEvent> Vecteur_Evnt; //Vecteur d'évènements

    QDate JourCours(2019, 1, 7);

    //Création d'un vecteur comprenant les dates des 365 jours de l'année
    for (int j = 0 ; j < 365 ; j++)
    {
        QDate JourCours2;
        JourCours2 = JourCours.addDays(j);
        Vecteur_JoursCours.push_back(JourCours2);
    }

    //Créations des Widgets de jours et affichage :
    int i = 0; //Compteur à incrémenter
    for(QDate JourCours : Vecteur_JoursCours)
    {
        Vecteur_Evnt = EDT.getEventList(JourCours); //Récupération dans un vecteur des évènements de la journée

        DayDisplay *EDT_Jour = new DayDisplay(JourCours, Vecteur_Evnt , nullptr, View); //Création du Jour

        //Création d'un proxy pour l'affichage dans le Scene
        QGraphicsProxyWidget* proxy = new QGraphicsProxyWidget;
        proxy->setWidget(EDT_Jour);
        proxy->moveBy(i*200 ,0); //Décalage incrémenté du Jours
        Scene->addItem(proxy);

        i++;
    }



    //——————————————————————————————————————————————————
    //   -- Organisation de la fenêtre
    //——————————————————————————————————————————————————

    View = new QGraphicsView(Scene); //Création de la vue
    View->setSceneRect((NUM_Semaine-1)*7*200 , 0 , (7*200),H); //Déplacement de la vue sur la semaine en cours

    //Création du Layout Général :
    QVBoxLayout* Layout_General = new QVBoxLayout (this);

    //Création du Layout de Contrôle
    QHBoxLayout* Layout_CTRL = new QHBoxLayout (this);

    //Affectation des Layout :
    Layout_CTRL->addWidget(Bouton1);
    Layout_CTRL->addWidget(Bouton2);
    Layout_CTRL->addWidget(Slider_Semaine);
    Layout_CTRL->addWidget(Text_Semaine);

    Layout_General->addLayout(Layout_CTRL);
    Layout_General->addWidget(View);

    QWidget* Widget_Final = new QWidget (this);
    Widget_Final->setLayout(Layout_General);
    setCentralWidget(Widget_Final);
    setMinimumSize(sizeHint());
//    setMaximumSize(sizeHint());
}

//Destructeur
MainWindow::~MainWindow(){}

//SLOT permettant de changer l'affichage de la semaine en changeant la position du Slider
void MainWindow::ModificationSemaine(int Value)
{
    View->setSceneRect((Value-1)*7*200 , 0 , (7*200),H);
    Text_Semaine->setText(QString::number(Value, 'i', 0)); //Affichage du texte
    var_value=Value;
}

//SLOT permettant d'afficher la semaine en cours
void MainWindow::MoveToToday()
{
    View->setSceneRect((NUM_Semaine-1)*7*200 , 0 , (7*200) , H); //Déplacement de la vue sur la semaine en cours
    Text_Semaine->setText(QString::number(NUM_Semaine, 'i', 0)); //Affichage du texte
    Slider_Semaine->setValue(NUM_Semaine);
}

//SLOT permettant de quitter le programme lorsque l'on clique sur le premier bouton
void MainWindow::End()
{
    qApp->quit();
}


void MainWindow::mousePressEvent(QMouseEvent *event){
//    if (event->button() == Qt::RightButton)
//    {
//        rightMousePressed = true;
//        _panStartX = event->x();
//        _panStartY = event->y();
//        setCursor(Qt::ClosedHandCursor);
//        event->accept();
//        return;

        QPoint p = event->pos();
        QGraphicsItem * l= View->itemAt(p);

        QGraphicsPixmapItem *image;
        if((image = dynamic_cast<QGraphicsPixmapItem *>(l))!=0){
            drag_item= image;
            start_drag_point =p;
            return;
        }
    //}
        drag_item = 0;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::RightButton)
    {
        rightMousePressed = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    event->ignore();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
//    if (rightMousePressed)
//    {
//        var_value= 0;
//        var_value += (event->x()-pos1);
//       // View->setSceneRect(0, 0 , (7*200)*52 , H);
//        View->mapToScene()
//        qInfo() << var_value;

//        _panStartX = event->x();

//        _panStartY = event->y();
//        event->accept();
//        pos1= event->x();
//        //Slider_Semaine->setValue( var_value);
//        return;
//    }
//    event->ignore();
    if(drag_item)
    {
        QPointF start = View->mapToScene(start_drag_point);
        QPointF stop = View->mapToScene(start_drag_point = event->pos());
        drag_item->moveBy(stop.x()-start.x(),0);
        View->update();
    }

}



