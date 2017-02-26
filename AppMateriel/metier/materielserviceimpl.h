#ifndef MATERIELSERVICEIMPL_H
#define MATERIELSERVICEIMPL_H
#include "physique/materieldataservice.h"
#include "metier/materielservice.h"
#include "physique/physiquefactory.h"
#include "metier/localisation.h"

namespace Metier {
class MaterielServiceImpl : public MaterielService
{
public:
    MaterielServiceImpl();
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
    Physique::MaterielDataService* materielDataSrv;
    Metier::LocalisationService* localisationSrv;
};
}

#endif // MATERIELSERVICEIMPL_H
