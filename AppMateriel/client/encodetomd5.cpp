#include "encodetomd5.h"

EncodeToMD5::EncodeToMD5()
{
}

EncodeToMD5::~EncodeToMD5()
{
}

QString EncodeToMD5::encode(QString password)
{
    QByteArray myByte;
    myByte.append(password);
    QByteArray hashMD5 = QCryptographicHash::hash(myByte, QCryptographicHash::Md5);
    QString cryptedPassword = hashMD5.toHex();
    return cryptedPassword;
}
