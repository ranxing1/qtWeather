#ifndef NETWORKER_H
#define NETWORKER_H
#include <QObject>
#include <QNetworkReply>

class QNetworkReply;

class NetWorker : public QObject{
    Q_OBJECT
public:
    static NetWorker* getInstance();
    ~NetWorker();

    QNetworkReply* get(const QString &url);

signals:
    void finished(QNetworkReply *reply);

private:
    class Private;
    friend class Private;
    Private *d;

    explicit NetWorker(QObject *parent = 0);
    NetWorker(const NetWorker &) Q_DECL_EQ_DELETE;
    NetWorker& operator=(NetWorker rhs) Q_DECL_EQ_DELETE;
};


#endif // NETWORKER_H
