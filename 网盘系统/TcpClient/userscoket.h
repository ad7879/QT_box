#ifndef USERSCOKET_H
#define USERSCOKET_H

#include <QTcpSocket>

class userScoket : public QTcpSocket
{
    Q_OBJECT
public:

    static userScoket *getSingle();

    ~userScoket();

signals:

public slots:

private:
    explicit userScoket(QObject *parent = 0);
    userScoket(const userScoket &other);

    static userScoket *single;
};

#endif // USERSCOKET_H
