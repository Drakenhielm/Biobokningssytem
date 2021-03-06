#include "basemodel.h"

BaseModel::BaseModel(const QString &tableName, const QString &primaryKey, QObject *parent)
    : QSqlQueryModel(parent)
{
    this->tableName = tableName;
    this->primaryKey = primaryKey;
}

bool BaseModel::removeRows(int row, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    if(row > rowCount())
        return false;
    if(count > 1)
        dh.transaction();
    bool ok = true;
    for(int i = 0; i < count; i++)
    {
        QSqlRecord rec(record(row));
        if(!rec.isEmpty())
        {
            QVariant pkValue = rec.value(primaryKey);
            if(pkValue.isValid())
                ok &= remove(pkValue);
        }
    }
    if(count > 1)
        return ok && dh.endTransaction(ok);
    else
        return ok;
}

/*Delete every row in the database where the value in "column" is equal to "value".
 * Calls remove function from DatabaseHandler. */
bool BaseModel::remove(const QVariant &pkValue)//(const QString &column, const QVariant &value)
{
    return dh.remove(tableName, primaryKey, pkValue);
}

/*Refresh model.
 * Populates the model with data from the database
 * using the specified sql statement and filter.*/
void BaseModel::refresh()
{
    query().exec();
    setQuery(query());
}

/*filter is the same as the where clause in a sql statement*/
void BaseModel::setFilter(const QString &filter, QVariant placeholder)
{
    QList<QVariant> list;
    list.append(placeholder);
    setFilter(filter, list);
}

void BaseModel::setFilter(const QString &filter, const QList<QVariant> &placeholderList)
{
    QSqlQuery query = this->query();
    if(lastFilterQuery == query.lastQuery())
    {
        dh.removeLastFilter(query);
    }
    dh.addFilter(query, filter, placeholderList);
    query.exec();
    setQuery(query);
    lastFilterQuery = query.lastQuery();
}

void BaseModel::clearFilter()
{
    QSqlQuery query = this->query();
    if(lastFilterQuery == query.lastQuery())
    {
        dh.removeLastFilter(query);
        /*QString sql = query.lastQuery();
        removeFilter(sql);
        prepareQuery(query, sql, getBoundValues(query));*/
        query.exec();
        setQuery(query);
        lastFilterQuery = "";
    }
}

/*Searches for a row in the model where the primary key value is equal to pkValue*/
int BaseModel::getRowByPrimaryKeyValue(const QVariant &pkValue) const
{
    int col = record().indexOf(primaryKey);
    QModelIndexList list;
    do
    {
        list = match(index(0, col), Qt::DisplayRole, pkValue, 1, Qt::MatchExactly);

    } while(list.isEmpty() && canFetchMore());

    if(list.isEmpty())
        return -1;

    return list.first().row();
}

QString BaseModel::dateTimeString(QDateTime dateTime) const
{
    if(dateTime.date() == QDate::currentDate())
        return dateTime.toString("'Today' H:mm");
    if(dateTime.date() == QDate::currentDate().addDays(1))
        return dateTime.toString("'Tomorrow' H:mm");
    return dateTime.toString("d/M/yy H:mm");
}
