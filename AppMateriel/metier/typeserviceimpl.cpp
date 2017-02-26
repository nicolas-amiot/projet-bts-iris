#include "typeserviceimpl.h"

Metier::TypeServiceImpl::TypeServiceImpl()
{
    typeDataSrv = PhysiqueFactory::getTypeDataServiceImpl();
    materielSrv = MetierFactory::getMaterielServiceImpl();
}

Type Metier::TypeServiceImpl::add(Type type)
{
    Type typ;
    if(!type.getNomType().isEmpty() && !type.getNomImage().isEmpty()){
        typ = typeDataSrv->add(type);
    }
    return typ;
}

bool Metier::TypeServiceImpl::remove(Type type)
{
    bool execute = false;
    if(type.getId() > 0){
        QList<Materiel> materiels = materielSrv->getByType(type, 0, materielSrv->getCountByType(type));
        if(materiels.isEmpty()){
            execute = typeDataSrv->remove(type);
        }
    }
    return execute;
}

bool Metier::TypeServiceImpl::update(Type type)
{
    bool execute = false;
    if(type.getId() > 0){
        if(!type.getNomType().isEmpty() && !type.getNomImage().isEmpty()){
            execute = typeDataSrv->update(type);
        }
    }
    return execute;
}

QList<Type> Metier::TypeServiceImpl::getAll(int debut, int parPage)
{
    QList<Type> typ;
    if(debut >= 0 && parPage > 0){
        typ = typeDataSrv->getAll(debut, parPage);
    }
    return typ;
}

int Metier::TypeServiceImpl::getCount()
{
    return typeDataSrv->getCount();
}

Type Metier::TypeServiceImpl::getById(long id)
{
    Type typ;
    if(id > 0){
        typ = typeDataSrv->getById(id);
    }
    return typ;
}

Type Metier::TypeServiceImpl::getByNomType(QString nomType)
{
    Type typ;
    if(!nomType.isEmpty()){
        typ = typeDataSrv->getByNomType(nomType);
    }
    return typ;
}

QList<QString> Metier::TypeServiceImpl::getListNomType(int debut, int parPage)
{
    QList<QString> listStr;
    if(debut >= 0 && parPage > 0){
        listStr = typeDataSrv->getListNomType(debut, parPage);
    }
    return listStr;
}

int Metier::TypeServiceImpl::getCountListNomType()
{
    int count = typeDataSrv->getCountListNomType();
    return count;
}

Type Metier::TypeServiceImpl::getByNomImage(QString nomImage)
{
    Type typ;
    if(!nomImage.isEmpty()){
        typ = typeDataSrv->getByNomImage(nomImage);
    }
    return typ;
}

QList<QString> Metier::TypeServiceImpl::getListNomImage(int debut, int parPage)
{
    QList<QString> listStr;
    if(debut >= 0 && parPage > 0){
        listStr = typeDataSrv->getListNomImage(debut, parPage);
    }
    return listStr;
}

int Metier::TypeServiceImpl::getCountListNomImage()
{
    int count = typeDataSrv->getCountListNomImage();
    return count;
}
