#ifndef ENCODETOMD5_H
#define ENCODETOMD5_H

#include <QString>
#include <QCryptographicHash>
#include <QByteArray>

class EncodeToMD5
{
public:
    EncodeToMD5();
    ~EncodeToMD5();
    QString encode(QString password);
};

#endif // ENCODETOMD5_H
