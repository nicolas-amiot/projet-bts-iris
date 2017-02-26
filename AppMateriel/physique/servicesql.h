#ifndef SERVICESQL_H
#define SERVICESQL_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlResult>
#include <QSqlError>

class ServiceSQL
{
public:
    ServiceSQL();
    ~ServiceSQL();
    bool databaseIsOpen();

private:
    QSqlDatabase db;	// référence sur base
};

#endif
