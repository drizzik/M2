#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QSlider>
#include <QLineEdit>
#include <QPushButton>

#include "DayDisplay.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private :
    QGraphicsView *View;
    QGraphicsScene *Scene;

    QPushButton *Bouton1;
    QPushButton *Bouton2;

    QSlider *Slider_Semaine;
    QLineEdit *Text_Semaine;
    bool _pan;
    int _panStartX, _panStartY;
    bool rightMousePressed;
    int pos1;
    qreal var_value;

    QGraphicsItem *drag_item;
    QPoint start_drag_point;

    int H = 500 ;
    int NUM_Semaine;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ModificationSemaine(int Value);
    void MoveToToday();
    void End();


    void mousePressEvent(QMouseEvent* e) override;
    void mouseReleaseEvent(QMouseEvent* e) override;
    void mouseMoveEvent(QMouseEvent*e) override;

};

#endif // MAINWINDOW_H
