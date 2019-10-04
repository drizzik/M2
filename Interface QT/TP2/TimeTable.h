#ifndef TIMETABLE_H
#define TIMETABLE_H
#include <map>
#include <vector>
using namespace std ;
#include "IcsEvent.h"

class TimeTable

{
private:
    map<QDate, vector<IcsEvent>> data_ ;
    void addEvent(const IcsEvent& ev) ;
public:
    explicit TimeTable();

    void loadFile( const QString &fname) ;
    QString searchTTFile(const QString& filename) ;
    vector<IcsEvent> &getEventList(const QDate& d) ;
    vector<QDate> getEventDateList() const ;
    QDate getFirstDate() const ;
    QDate getLastDate() const ;
    int getDayCount() const;
    // utile seulement en phase de mise au point
    friend ostream& operator<<(ostream& o, const TimeTable &t) ;
};

#endif // TIMETABLE_H
