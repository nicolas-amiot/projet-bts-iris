#ifndef PORTIQUE_H
#define PORTIQUE_H
#include <QString>
#include <QList>
#include "salle.h"
#include "lecteurrfid.h"

class Portique
{
private:
    long id;
    float x;
    float y;
    Salle salle1;
    Salle salle2;
    LecteurRFID lecteur;
public:
    Portique();
    Portique(float x, float y, Salle salle1, Salle salle2, LecteurRFID lecteur);
    ~Portique();

    long getId(void);
    float getX(void);
    float getY(void);
    Salle getSalle1(void);
    Salle getSalle2(void);
    LecteurRFID getLecteurRFID(void);

    void setId(long id);
    void setX(float x);
    void setY(float y);
    void setSalle1(Salle salle1);
    void setSalle2(Salle salle2);
    void setLecteurRFID(LecteurRFID lecteur);
};

#endif // PORTIQUE_H
