#ifndef TYPESERVICE_H
#define TYPESERVICE_H
#include "metier/type.h"

namespace Metier {
class TypeService
{
public:
    virtual Type add(Type type) = 0;
    virtual bool remove(Type type) = 0;
    virtual bool update(Type type) = 0;
    virtual QList<Type> getAll(int debut, int parPage) = 0;
    virtual int getCount() = 0;
    virtual Type getById(long id) = 0;
    virtual Type getByNomType(QString nomType) = 0;
    virtual QList<QString> getListNomType(int debut, int parPage) = 0;
    virtual int getCountListNomType() = 0;
    virtual Type getByNomImage(QString nomImage) = 0;
    virtual QList<QString> getListNomImage(int debut, int parPage) = 0;
    virtual int getCountListNomImage() = 0;
};
}

#endif // TYPESERVICE_H
