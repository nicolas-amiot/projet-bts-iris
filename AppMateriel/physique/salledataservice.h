#ifndef SALLEDATASERVICE_H
#define SALLEDATASERVICE_H
#include "metier/salle.h"

namespace Physique {
class SalleDataService
{
public:
    virtual Salle add(Salle salle) = 0;
    virtual bool remove(Salle salle) = 0;
    virtual bool update(Salle salle) = 0;
    virtual QList<Salle> getAll(int debut, int parPage) = 0;
    virtual int getCount() = 0;
    virtual Salle getById(long id) = 0;
    virtual QList<Salle> getByNomSalle(QString nomSalle, int debut, int parPage) = 0;
    virtual int getCountByNomSalle(QString nomSalle) = 0;
    virtual QList<QString> getListNomSalle(int debut, int parPage) = 0;
    virtual int getCountListNomSalle() = 0;
    virtual Salle getByNumSalle(int numSalle) = 0;
    virtual QList<int> getListNumSalle(int debut, int parPage) = 0;
    virtual int getCountListNumSalle() = 0;
    virtual QList<Salle> getByNomAtelier(QString nomAtelier, int debut, int parPage) = 0;
    virtual int getCountByNomAtelier(QString nomAtelier) = 0;
    virtual QList<QString> getListNomAtelier(int debut, int parPage) = 0;
    virtual int getCountListNomAtelier() = 0;
};
}

#endif // SALLEDATASERVICE_H
