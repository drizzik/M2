#include "IcsEvent.h"

IcsEvent::IcsEvent(const QString& desc, const QString& loc, const QDateTime& b, const QDateTime& e)
 : summary_(desc), location_(loc), begin_(b), end_(e)
{

}
QDate IcsEvent::date() const
{
    return begin_.date() ;
}
QTime IcsEvent::start() const
{
    return begin_.time() ;
}

QTime IcsEvent::stop() const
{
    return end_.time() ;
}

QString IcsEvent::what() const
{
    return summary_ ;
}

QString IcsEvent::prof() const
{
    return prof_ ;
}

QString IcsEvent::where() const
{
    return location_ ;
}

void IcsEvent::clear()
{
    // un evènement sans description est  supposé nul
    summary_.clear() ;
}

ostream& operator<<(ostream& o, const IcsEvent& e)
{
    o << endl << "*** " ;
    o << e.start().toString().toStdString() << " -> " << e.stop().toString().toStdString() << endl  ;
    QString w = e.what() ;
    w = w.replace("\\n","\n") ;
    o <<   w.toStdString() << endl << e.where().toStdString() ;
    return o   ;
}

bool IcsEvent::operator<(const IcsEvent& x) const
{
    return begin_ < x.begin_ ;
}
