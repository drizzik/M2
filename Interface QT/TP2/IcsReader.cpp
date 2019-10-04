#include "IcsReader.h"
#include <iostream>
using namespace std ;

IcsReader::IcsReader(const QString &filename)
{
    file_.setFileName(filename);
    if( !file_.open(QIODevice::ReadOnly) ) throw "ICSReader: file not found." ;
    stream_.setDevice(&file_);
}

QString IcsReader::nextLine()
{
    QString L = stream_.readLine() ;
    // ligne suite ?
    auto ici = stream_.pos() ;
    QString C = stream_.readLine(1) ;
    stream_.seek(ici) ;
    if( C == " " ) L += nextLine() ;

    return L ;
}

bool  IcsReader::splitCommand(const QString& line, QString& key, QString& value)
{
    key.clear(); value.clear();
    for(int i = 0 ; i < line.size() ; ++i)
    {
        if( line[i] == ':' )
        {
            key = line.left(i) ;
            value = line.right(line.size() - i - 1) ;
            return true ;
        }
    }
    return false ;
}

bool IcsReader::nextKeyValue(QString& K, QString& V)
{
    if( IcsReader::splitCommand( nextLine(),  K,V)) return true ;
    return false ;
}

//
// Decode une date au format 'Z'
// les autres encodages sont rejetés
//
bool IcsReader::decodeDate( const QString &txt, QDateTime& dt)
{
    if(  txt[8] != 'T' || txt[15] != 'Z' ) return false ;
    int annee = txt.mid(0,4).toInt() ;
    int mois = txt.mid(4,2).toInt() ;
    int jour = txt.mid(6,2).toInt() ;
    int heure = txt.mid(9,2).toInt() ;
    int minute = txt.mid(11,2).toInt() ;
    int seconde = txt.mid(13,2).toInt() ;

    dt = QDateTime(QDate(annee,mois,jour), QTime(heure,minute,seconde)) ;
    // correction: UTC+2 en été, +1 en hiver !!
    // une solution plus correcte, mais BEAUCOUP plus lourde est basée sur les QTimeZone
    // le résultat ci-dessous est FAUX en heure d'hiver
    dt = dt.addSecs(2*3600) ;
    return true ;
}


bool IcsReader::parseEvent(IcsEvent &evnt)
{
    auto ici = stream_.pos() ;
    evnt.clear();

    QString K,V ;
    if( nextKeyValue(K,V) && K == "BEGIN" && V == "VEVENT")
    {
        while( nextKeyValue(K,V) )
        {
            if((K == "END" && V == "VEVENT")  ) return true ;
            else if( K == "SUMMARY") evnt.summary_ = V ;
            else if( K == "LOCATION") evnt.location_ = V ;
            else if( K == "DTSTART" && IcsReader::decodeDate(V, evnt.begin_) ) {}
            else if( K == "DTEND" && IcsReader::decodeDate(V, evnt.end_) ) {}
            else if( K == "DESCRIPTION") evnt.prof_ = parseProf(V);
            // les autres mot-clé sont ignorés
        }
        // fin evènement non détectée .. pas normal
    }
    // dans les 2 cas, echec. On revient au point de départ.
    // Attention, seek est coûteux, mais normalement on ne doit pas y recourir
    stream_.seek(ici ) ;
    return false ;
}

bool IcsReader::parseHeader()
{
    QString K,V ;
    if( !nextKeyValue(K,V) || K != "BEGIN" || V != "VCALENDAR" )
        return false ; // pas de retour arrière
    auto ici = stream_.pos() ;
    while (nextKeyValue(K,V) && !( K == "BEGIN" && V == "VEVENT"))
        ici = stream_.pos()  ;  // tout lire jusqu'au 1er evenement.
    stream_.seek(ici) ; // revenir au début de l'évènement
    return true ;
}

bool IcsReader::parseFooter()
{
    QString K,V ;
    auto ici = stream_.pos() ;
    if( !nextKeyValue(K,V) || K != "END" || V != "VCALENDAR" )
    {
        stream_.seek(ici)  ;
        return false ;
    }
    return true ;
}
// Recherche spécifiquement le prof dans la rubrique "DESCRIPTION"
QString IcsReader::parseProf( QString desc)
{
    QString r ;

    desc.replace("\\,", "," ) ;
    int k = desc.indexOf("\\nProf : ") ;
    if( k != -1)
    {
        k += 9 ;
        for(  ; k < desc.size() && desc[k] != QChar('\\') ; ++k )
        {
            r += desc[k] ;
        }
    }
    return r ;
}
