#ifndef BATIMENT_H
#define BATIMENT_H
#include <QString>
#include <QList>
#include "salle.h"

class Batiment
{
private:
    long id;
    QString nomBatiment;
    QList<Salle> salles;
    QString plan;
public:
    Batiment();
    Batiment(QString nomBatiment, QList<Salle> salles, QString plan);
    ~Batiment();

    long getId(void);
    QString getNomBatiment(void);
    QList<Salle> getSalles(void);
    QString getPlan(void);

    void setId(long id);
    void setNomBatiment(QString nomBatiment);
    void setSalles(QList<Salle> salles);
    void setPlan(QString plan);
};


#endif // BATIMENT_H
