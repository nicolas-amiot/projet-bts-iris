#ifndef MATERIELDATASERVICEIMPL_H
#define MATERIELDATASERVICEIMPL_H
#include "physique/materieldataservice.h"
#include "metier/metierfactory.h"
#include "physique/typedataservice.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

namespace Physique {
class MaterielDataServiceImpl : public MaterielDataService
{
public:
    MaterielDataServiceImpl();
    virtual Materiel add(Materiel materiel);
    virtual bool remove(Materiel materiel);
    virtual bool update(Materiel materiel);
    virtual QList<Materiel> getAll(int debut, int parPage);
    virtual int getCount();
    virtual Materiel getById(long id);
    virtual Materiel getByIdBadge(QString idBadge);
    virtual QList<QString> getListIdBadge(int debut, int parPage);
    virtual int getCountListIdBadge();
    virtual QList<Materiel> getByDateControle(QDate dateControle, int debut, int parPage);
    virtual int getCountByDateControle(QDate dateControle);
    virtual QList<QDate> getListDateControle(int debut, int parPage);
    virtual int getCountListDateControle();
    virtual QList<Materiel> getByNewDateControle(QDate newDateControle, int debut, int parPage);
    virtual int getCountByNewDateControle(QDate newDateControle);
    virtual QList<QDate> getListNewDateControle(int debut, int parPage);
    virtual int getCountListNewDateControle();
    virtual QList<Materiel> getByPeriode(QDate date, bool avant, int debut, int parPage);
    virtual int getCountByPeriode(QDate date, bool avant);
    virtual QList<Materiel> getByType(Type type, int debut, int parPage);
    virtual int getCountByType(Type type);
    virtual QList<Type>getListType(int debut, int parPage);
    virtual int getCountListType();
    virtual QList<Materiel>getByNomMateriel(QString nomMateriel, int debut, int parPage);
    virtual int getCountByNomMateriel(QString nomMateriel);
    virtual QList<QString>getListNomMateriel(int debut, int parPage);
    virtual int getCountListNomMateriel();
private:
    QSqlQuery query;
    Physique::TypeDataService* typeDataSrv;
};
}

#endif // MATERIELDATASERVICEIMPL_H
