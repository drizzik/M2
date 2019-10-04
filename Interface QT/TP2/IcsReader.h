#ifndef ICSREADER_H
#define ICSREADER_H
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include "IcsEvent.h"
class TimeTable ;

class IcsReader
{
    QFile file_ ;
    QTextStream stream_ ;
public:
    IcsReader(const QString &filename);
    QString nextLine() ;
    bool nextKeyValue(QString& K, QString& V) ;
    static bool splitCommand(const QString& line, QString& key, QString& value) ;
    static bool decodeDate( const QString &txt, QDateTime& dt) ;
    bool parseEvent(IcsEvent &) ;
    bool parseHeader() ;
    bool parseFooter() ;
    bool parseTimeTable(TimeTable& tab) ;
    QString parseProf(QString desc) ;
};

#endif // ICSREADER_H
