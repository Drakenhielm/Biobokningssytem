#ifndef BASEMODEL_H
#define BASEMODEL_H

#include <QSqlRelationalTableModel>

class BaseModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:
    BaseModel(const QString &tableName, QObject *parent = 0);
    BaseModel(const QString & tableName, const QString & query = QString(), QObject *parent = 0);

signals:

public slots:

private:
    //hide derived functions
    void setTable(const QString &tableName);
    void setQuery(const QSqlQuery &query);

    void initBaseModel(const QString & tableName, const QString & query = QString());

};

#endif // BASEMODEL_H