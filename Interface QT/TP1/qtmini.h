#ifndef QTMINI_H
#define QTMINI_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>

class QtMini : public QMainWindow
{
    Q_OBJECT
    QLabel *labelBtn;
    QLineEdit *lineSlider;
    QLabel *lineRadio;
    QTextEdit *textDialog;
    QColorDialog *qcdialog;
    QTextEdit *textCombo;

public:
    QtMini();

signals:

public slots:
    void btnPressed();
    void btnReleased();
    void changeValue(int value);
    void onRb2Clicked();
    void onRb1Clicked();
    void setBackgroundColor();
    void displayChoice(int value);
};

#endif // QTMINI_H
