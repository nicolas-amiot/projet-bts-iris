#ifndef MATERIEL_H
#define MATERIEL_H
#include <QDate>
#include <QString>
#include <QList>
#include "type.h"


class Materiel
{
    private:
        long id;
        QString idBadge;
        QDate dateControle;
        QDate newDateControle;
        QString nomMateriel;
        Type type;
    public:
        Materiel();
        Materiel(QString idBadge, QDate dateControle, QDate newDateControle, QString nomMateriel, Type type);
        ~Materiel();

        long getId(void);
        QString getIdBadge(void);
        QDate getDateControle(void);
        QDate getNewDateControle(void);
        QString getNomMateriel(void);
        Type getType(void);

        void setId(long id);
        void setDateControle(QDate dateControle);
        void setNewDateControle(QDate newDateControle);
        void setNomMateriel(QString nomMateriel);
        void setIdBadge(QString idBadge);
        void setType(Type type);
};


#endif // MATERIEL_H
