#ifndef QTMINI_H
#define QTMINI_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include <QTimer>

class QtMini : public QMainWindow
{
    Q_OBJECT
    QLabel *labelBtn;
    QLineEdit *lineSlider;
    QLabel *lineRadio;
    QTextEdit *textDialog;
    QTextEdit *textCombo;
    QProgressBar *qProgressBar;

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
    void updateProgress();
};

#endif // QTMINI_H
