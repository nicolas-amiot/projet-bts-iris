#include "typedataserviceimpl.h"

Physique::TypeDataServiceImpl::TypeDataServiceImpl()
{
}

Type Physique::TypeDataServiceImpl::add(Type type)
{
    Type newType;
    query.prepare("INSERT INTO type (nomType, nomImage) VALUES (:nomType, :nomImage)");
    query.bindValue(":nomType", type.getNomType());
    query.bindValue(":nomImage", type.getNomImage());
    if(query.exec()) {
        newType = getById(query.lastInsertId().toLongLong());
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return newType;
}

bool Physique::TypeDataServiceImpl::remove(Type type)
{
    bool execute;
    query.prepare("DELETE FROM type WHERE id = :id");
    query.bindValue(":id", (qlonglong)type.getId());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

bool Physique::TypeDataServiceImpl::update(Type type)
{
    bool execute;
    query.prepare("UPDATE type SET nomType = :nomType, nomImage = :nomImage WHERE id = :id");
    query.bindValue(":id", (qlonglong)type.getId());
    query.bindValue(":nomType", type.getNomType());
    query.bindValue(":nomImage", type.getNomImage());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

QList<Type> Physique::TypeDataServiceImpl::getAll(int debut, int parPage)
{
    QList<Type> types;
    Type type;
    query.prepare("SELECT * FROM type ORDER BY nomType ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            type = Type(query.value(1).toString(), query.value(2).toString());
            type.setId(query.value(0).toLongLong());
            types.append(type);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return types;
}

int Physique::TypeDataServiceImpl::getCount()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM type");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Type Physique::TypeDataServiceImpl::getById(long id)
{
    Type type;
    query.prepare("SELECT * FROM type WHERE id = :id");
    query.bindValue(":id", (qlonglong)id);
    if(query.exec()) {
        if(query.next())
        {
            type = Type(query.value(1).toString(), query.value(2).toString());
            type.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return type;
}

Type Physique::TypeDataServiceImpl::getByNomType(QString nomType)
{
    Type type;
    query.prepare("SELECT * FROM type WHERE nomType = :nomType");
    query.bindValue(":nomType", nomType);
    if(query.exec()) {
        if(query.next())
        {
            type = Type(query.value(1).toString(), query.value(2).toString());
            type.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return type;
}

QList<QString> Physique::TypeDataServiceImpl::getListNomType(int debut, int parPage)
{
    QList<QString> listNomType;
    query.prepare("SELECT nomType FROM type WHERE nomType != '' ORDER BY nomType ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listNomType.append(query.value(0).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listNomType;
}

int Physique::TypeDataServiceImpl::getCountListNomType()
{
    int count = 0;
    query.prepare("SELECT COUNT(nomType) FROM type WHERE nomType != ''");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Type Physique::TypeDataServiceImpl::getByNomImage(QString nomImage)
{
    Type type;
    query.prepare("SELECT * FROM type WHERE nomImage = :nomImage");
    query.bindValue(":nomImage", nomImage);
    if(query.exec()) {
        if(query.next())
        {
            type = Type(query.value(1).toString(), query.value(2).toString());
            type.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return type;
}

QList<QString> Physique::TypeDataServiceImpl::getListNomImage(int debut, int parPage)
{
    QList<QString> listNomImage;
    query.prepare("SELECT nomImage FROM type WHERE nomImage != '' ORDER BY nomImage ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listNomImage.append(query.value(0).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listNomImage;
}

int Physique::TypeDataServiceImpl::getCountListNomImage()
{
    int count = 0;
    query.prepare("SELECT COUNT(nomImage) FROM type WHERE nomImage != ''");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

