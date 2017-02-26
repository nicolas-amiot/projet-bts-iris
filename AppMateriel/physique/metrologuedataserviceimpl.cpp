#include "metrologuedataserviceimpl.h"

Physique::MetrologueDataServiceImpl::MetrologueDataServiceImpl()
{
}

Metrologue Physique::MetrologueDataServiceImpl::add(Metrologue metrologue)
{
    Metrologue newMetrologue;
    query.prepare("INSERT INTO metrologue (login, password) VALUES (:login, :password)");
    query.bindValue(":login", metrologue.getLogin());
    query.bindValue(":password", metrologue.getPassword());
    if(query.exec()) {
        newMetrologue = getById(query.lastInsertId().toLongLong());
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return newMetrologue;
}

bool Physique::MetrologueDataServiceImpl::remove(Metrologue metrologue)
{
    bool execute;
    query.prepare("DELETE FROM metrologue WHERE id = :id");
    query.bindValue(":id", (qlonglong)metrologue.getId());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

bool Physique::MetrologueDataServiceImpl::update(Metrologue metrologue)
{
    bool execute;
    query.prepare("UPDATE metrologue SET login = :login, password = :password WHERE id = :id");
    query.bindValue(":id", (qlonglong)metrologue.getId());
    query.bindValue(":login", metrologue.getLogin());
    query.bindValue(":password", metrologue.getPassword());
    if(!(execute = query.exec())) {
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return execute;
}

QList<Metrologue> Physique::MetrologueDataServiceImpl::getAll(int debut, int parPage)
{
    QList<Metrologue> metrologues;
    Metrologue metrologue;
    query.prepare("SELECT * FROM metrologue ORDER BY login ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next())
        {
            metrologue = Metrologue(query.value(1).toString(), query.value(2).toString());
            metrologue.setId(query.value(0).toLongLong());
            metrologues.append(metrologue);
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return metrologues;
}

int Physique::MetrologueDataServiceImpl::getCount()
{
    int count = 0;
    query.prepare("SELECT COUNT(*) FROM metrologue");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}

Metrologue Physique::MetrologueDataServiceImpl::getById(long id)
{
    Metrologue metrologue;
    query.prepare("SELECT * FROM metrologue WHERE id = :id");
    query.bindValue(":id", (qlonglong)id);
    if(query.exec()) {
        if(query.next())
        {
            metrologue = Metrologue(query.value(1).toString(), query.value(2).toString());
            metrologue.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return metrologue;
}

Metrologue Physique::MetrologueDataServiceImpl::getByLogin(QString login)
{
    Metrologue metrologue;
    query.prepare("SELECT * FROM metrologue WHERE login = :login");
    query.bindValue(":login", login);
    if(query.exec()) {
        if(query.next())
        {
            metrologue = Metrologue(query.value(1).toString(), query.value(2).toString());
            metrologue.setId(query.value(0).toLongLong());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return metrologue;
}

QList<QString> Physique::MetrologueDataServiceImpl::getListLogin(int debut, int parPage)
{
    QList<QString> listLogin;
    query.prepare("SELECT login FROM metrologue WHERE login != '' ORDER BY login ASC LIMIT :debut,:parPage");
    query.bindValue(":debut", debut);
    query.bindValue(":parPage", parPage);
    if(query.exec()) {
        while(query.next()){
            listLogin.append(query.value(0).toString());
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return listLogin;
}

int Physique::MetrologueDataServiceImpl::getCountListLogin()
{
    int count = 0;
    query.prepare("SELECT COUNT(login) FROM metrologue WHERE login != ''");
    if(query.exec()) {
        if(query.next()){
            count = query.value(0).toInt();
        }
    }else{
        qWarning("Error: %s\n", query.lastError().text().toLatin1().data());
    }
    return count;
}
