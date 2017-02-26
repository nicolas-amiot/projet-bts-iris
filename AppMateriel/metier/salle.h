#ifndef SALLE_H
#define SALLE_H
#include <QList>
#include <QString>

class Salle
{
private:
    long id;
    float x_ini;
    float y_ini;
    float x_fin;
    float y_fin;
    int numSalle;
    QString nomSalle;
    QString nomAtelier;
public:
    Salle();
    Salle(float x_ini,float y_ini, float x_fin, float y_fin, int numSalle, QString nomSalle, QString nomAtelier);
    ~Salle();

    long getId(void);
    float getX_ini(void);
    float getY_ini(void);
    float getX_fin(void);
    float getY_fin(void);
    int getNumSalle(void);
    QString getNomSalle(void);
    QString getNomAtelier(void);

    void setId(long id);
    void setX_ini(float x_ini);
    void setY_ini(float y_ini);
    void setX_fin(float x_fin);
    void setY_fin(float y_fin);
    void setNumSalle(int numSalle);
    void setNomSalle(QString nomSalle);
    void setNomAtelier(QString nomAtelier);

};

#endif // SALLE_H
