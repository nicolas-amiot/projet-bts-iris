#ifndef TYPEDATASERVICEIMPL_H
#define TYPEDATASERVICEIMPL_H
#include "physique/typedataservice.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

namespace Physique {
class TypeDataServiceImpl : public TypeDataService
{
public:
    TypeDataServiceImpl();
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
    QSqlQuery query;
};
}

#endif // TYPEDATASERVICEIMPL_H
