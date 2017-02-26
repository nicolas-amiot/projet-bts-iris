#include "type.h"

Type::Type()
{
    this->id = 0;
    this->nomType = QString();
    this->nomImage = QString();
}

Type::Type(QString nomType, QString nomImage)
{
    this->id = 0;
    this->nomType = nomType;
    this->nomImage = nomImage;
}

Type::~Type()
{
}

long Type::getId()
{
    return this->id;
}

QString Type::getNomType()
{
    return this->nomType;
}

QString Type::getNomImage()
{
    return this->nomImage;
}

void Type::setId(long id)
{
    this->id = id;
}

void Type::setNomType(QString nomType)
{
    this->nomType = nomType;
}

void Type::setNomImage(QString nomImage)
{
    this->nomImage = nomImage;
}
