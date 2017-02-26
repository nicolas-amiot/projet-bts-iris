#ifndef METROLOGUE_H
#define METROLOGUE_H
#include <QString>
#include <QList>


class Metrologue
{
private:
    long id;
    QString login;
    QString password;
public:
    Metrologue();
    Metrologue(QString login,QString password);
    ~Metrologue();

    long getId(void);
    QString getLogin(void);
    QString getPassword(void);

    void setId(long id);
    void setLogin(QString login);
    void setPassword(QString password);

};


#endif // METROLOGUE_H
