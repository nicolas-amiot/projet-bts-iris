#ifndef TYPE_H
#define TYPE_H
#include <QString>
#include <QList>

class Type
{
private:
    long id;
    QString nomType;
    QString nomImage;
public:
    Type();
    Type(QString nomType, QString nomImage);
    ~Type();

    long getId(void);
    QString getNomType(void);
    QString getNomImage(void);

    void setId(long id);
    void setNomType(QString nomType);
    void setNomImage(QString nomImage);
};

#endif // TYPE_H
