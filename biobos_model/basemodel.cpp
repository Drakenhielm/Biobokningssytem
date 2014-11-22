#include "basemodel.h"

BaseModel::BaseModel(const QString &tableName, QObject *parent)
    : QSqlQueryModel(parent)
{
    initBaseModel(tableName, QString());
}

BaseModel::BaseModel(const QString &tableName, const QString &query, QObject *parent)
    : QSqlQueryModel(parent)
{
    initBaseModel(tableName, query);
}

void BaseModel::initBaseModel(const QString & tableName, const QString & queryStr)
{
    //setTable(tableName);
    //QSqlQuery query;
    if(queryStr.isEmpty())
    {
        setQuery("select * from "+tableName);
    }
    else
    {
        setQuery(queryStr);
    }
    //setQuery(query);
    //setEditStrategy(OnManualSubmit);
}

QVariant BaseModel::data(const QModelIndex &item, int role) const
{
    QVariant value = QSqlQueryModel::data(item, role);
    if (value.isValid() && role == Qt::DisplayRole) {
        if(record().fieldName(item.column()) == "DateTime")
        {
            return value.toDateTime().toString("d/M/yy H:mm");
        }
    }
    return QSqlQueryModel::data(item, role);
}

/*bool BaseModel::submitAll(bool insideTransaction)
{
    if(insideTransaction)
    {
        database().transaction();
        if(QSqlTableModel::submitAll())
        {
            return database().commit();
        }
        else
        {
            database().rollback();
            qDebug() << "The database reported an error: "
                     << lastError().text();
            return false;
        }
    }
    return QSqlTableModel::submitAll();
}*/

bool BaseModel::deleteWhere(const QString &column, const QVariant &value)
{

    return dh.remove("movie"/*tableName()*/, column, value);
}

/*void BaseModel::setTable(const QString &tableName)
{
    QSqlRelationalTableModel::setTable(tableName);
}*/

/*Refresh model*/
void BaseModel::refresh()
{
    setQuery(query());
    query().exec();
}
