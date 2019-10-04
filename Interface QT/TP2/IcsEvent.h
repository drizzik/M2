#ifndef ICSEVENT_H
#define ICSEVENT_H
#include <QString>
#include <QDateTime>
#include <iostream>
using namespace std ;

class IcsEvent
{
public:
    QString summary_ , location_ , prof_ ;
    QDateTime begin_, end_ ;
public:
    explicit IcsEvent(const QString& desc=QString(), const QString& loc=QString(),
             const QDateTime &b=QDateTime() , const QDateTime &e=QDateTime() ) ;
    QDate date() const ;
    QTime start() const ;
    QTime stop() const ;
    QString where() const ;
    QString what() const ;
    QString prof() const ;
    void clear() ;
    friend ostream& operator<<(ostream&, const IcsEvent&) ;
    bool operator<(const IcsEvent& ) const ;
};

#endif // ICSEVENT_H
