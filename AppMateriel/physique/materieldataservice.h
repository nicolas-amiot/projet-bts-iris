#ifndef MATERIELDATASERVICE_H
#define MATERIELDATASERVICE_H
#include "metier/materiel.h"

namespace Physique {
class MaterielDataService
{
public:
    virtual Materiel add(Materiel materiel) = 0;
    virtual bool remove(Materiel materiel) = 0;
    virtual bool update(Materiel materiel) = 0;
    virtual QList<Materiel> getAll(int debut, int parPage) = 0;
    virtual int getCount() = 0;
    virtual Materiel getById(long id) = 0;
    virtual Materiel getByIdBadge(QString idBadge) = 0;
    virtual QList<QString> getListIdBadge(int debut, int parPage) = 0;
    virtual int getCountListIdBadge() = 0;
    virtual QList<Materiel> getByDateControle(QDate dateControle, int debut, int parPage) = 0;
    virtual int getCountByDateControle(QDate dateControle) = 0;
    virtual QList<QDate> getListDateControle(int debut, int parPage) = 0;
    virtual int getCountListDateControle() = 0;
    virtual QList<Materiel> getByNewDateControle(QDate newDateControle, int debut, int parPage) = 0;
    virtual int getCountByNewDateControle(QDate newDateControle) = 0;
    virtual QList<QDate> getListNewDateControle(int debut, int parPage) = 0;
    virtual int getCountListNewDateControle() = 0;
    virtual QList<Materiel> getByPeriode(QDate date, bool avant, int debut, int parPage) = 0;
    virtual int getCountByPeriode(QDate date, bool avant) = 0;
    virtual QList<Materiel> getByType(Type type, int debut, int parPage) = 0;
    virtual int getCountByType(Type type) = 0;
    virtual QList<Type>getListType(int debut, int parPage) = 0;
    virtual int getCountListType() = 0;
    virtual QList<Materiel>getByNomMateriel(QString nomMateriel, int debut, int parPage) = 0;
    virtual int getCountByNomMateriel(QString nomMateriel) = 0;
    virtual QList<QString>getListNomMateriel(int debut, int parPage) = 0;
    virtual int getCountListNomMateriel() = 0;
};
}

#endif // MATERIELDATASERVICE_H
