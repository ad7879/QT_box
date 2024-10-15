#include "userscoket.h"

userScoket * userScoket::single = new userScoket;

userScoket *userScoket::getSingle()
{
    return single;
}

userScoket::userScoket(QObject *parent) : QTcpSocket(parent)
{

}

userScoket::~userScoket()
{

}

