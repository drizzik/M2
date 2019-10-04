#include "TimeTable.h"
#include "IcsReader.h"

#include <QDir>
#include <QDebug>

#include <algorithm>
using namespace std ;

TimeTable::TimeTable()
{
}

void TimeTable::addEvent(const IcsEvent& ev)
{
    auto& entry=data_[ev.date()]   ;
    entry.push_back(ev) ;
    sort(entry.begin(), entry.end()) ; // en principe inutile
}

vector<IcsEvent> &TimeTable::getEventList(const QDate&  d)
{
    // il faut éviter de creer des entrées pour rien dans la
    // table. Si l'entrée n'existe pas, on retourne simlement une vecteur vide.
    static vector<IcsEvent> rien ; // STATIQUE !
    auto entry = data_.find(d) ;
    if( entry == data_.end() ) return rien ;
    return (*entry).second ;
}

vector<QDate> TimeTable::getEventDateList() const
{
    vector<QDate> r ;

    for( const auto& ev : data_ )
        r.push_back(ev.first );
    return r ;
}

void TimeTable::loadFile( const QString &fname)
{
    IcsReader reader(fname) ; // may throw
    IcsEvent ev ;


    if( reader.parseHeader())
    {
        while(reader.parseEvent(ev))
        {
            addEvent(ev);
        }
        if( ! reader.parseFooter())
            throw "Missing file footer" ;

    }
    else
        throw "Missing file header" ;
}


ostream& operator<<(ostream& o , const TimeTable &t)
{
    TimeTable& tt = const_cast< TimeTable &>(t) ;
    auto dates =  tt.getEventDateList() ;

    for( auto date : dates )
    {
        cout << "------------ " << date.toString().toStdString() << "------------ " << endl ;
        vector<IcsEvent>&  events = tt.getEventList(date) ;
        for(const  IcsEvent& e : events)
        {
            cout << e << endl ;
        }
    }
    return o ;
}
//
// Heuristique pour decouvrir le chemin d'accès au fichier Emploi du Temps
// sur la machine hôte
// Quick and dirty, à affiner ...
//
QString TimeTable::searchTTFile(const QString& filename)
{
    QFile f ;
    QString n ;

    static const char *paths[] =
    {
        "/storage/sdcard0/My Documents/",
        "/storage/sdcard0/Download/",
        "/storage/emulated/0/My Documents/",
        "/storage/emulated/0/Download/",
        "../", "./"
    };

    for( auto p : paths )
    {
        f.setFileName(n = p+filename);
        if( f.exists()) return n ;
    }
    return  "";
}

QDate TimeTable::getFirstDate() const
{
    if( data_.empty()) return QDate::currentDate() ;
    auto firstday = data_.begin() ;
    return (*firstday).first ;
}

QDate TimeTable::getLastDate() const
{
    if( data_.empty()) return QDate::currentDate() ;
    auto lastday = data_.rbegin() ;
    return (*lastday).first ;
}

int TimeTable::getDayCount() const
{
    return data_.size() ;
}
