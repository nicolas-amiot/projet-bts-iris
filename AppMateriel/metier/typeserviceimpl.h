#ifndef TYPESERVICEIMPL_H
#define TYPESERVICEIMPL_H
#include "physique/typedataservice.h"
#include "metier/typeservice.h"
#include "physique/physiquefactory.h"
#include "metier/materielservice.h"

namespace Metier {
class TypeServiceImpl : public TypeService
{
public:
    TypeServiceImpl();
    virtual Type add(Type type);
    virtual bool remove(Type type);
    virtual bool update(Type type);
    virtual QList<Type> getAll(int debut, int parPage);
    virtual int getCount();
    virtual Type getById(long id);
    virtual Type getByNomType(QString nomType);
    virtual QList<QString> getListNomType(int debut, int parPage);
    virtual int getCountListNomType();
    virtual Type getByNomImage(QString nomImage);
    virtual QList<QString> getListNomImage(int debut, int parPage);
    virtual int getCountListNomImage();
private:
    Physique::TypeDataService* typeDataSrv;
    Metier::MaterielService* materielSrv;
};
}

#endif // TYPESERVICEIMPL_H
