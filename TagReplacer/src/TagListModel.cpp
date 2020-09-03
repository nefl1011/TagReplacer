#include "TagListModel.h"
#include "TagList.h"

TagListModel::TagListModel(QObject *parent)
    : QAbstractListModel(parent)
    , tagList(nullptr)
{
}

int TagListModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid() || !tagList)
        return 0;

    return tagList->items().size();
}

QVariant TagListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || !tagList)
        return QVariant();

    const Tag item = tagList->items().at(index.row());
    switch (role) {
    case IdRole:
        return QVariant(item.id);
    case TagNameRole:
        return QVariant(item.tag);
    case DescriptionRole:
        return QVariant(item.errorMessage);
    case ValidRole:
        return QVariant(item.isValid);
    case EscapingRole:
        return QVariant(item.isEscaped);
    }

    return QVariant();
}

bool TagListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!tagList)
        return false;

    Tag item = tagList->items().at(index.row());

    switch (role) {
    case IdRole:
        item.id = value.toInt();
        break;
    case TagNameRole:
        item.tag = value.toString();
        break;
    case DescriptionRole:
        item.errorMessage = value.toString();
    case ValidRole:
        item.isValid = value.toBool();
        break;
    case EscapingRole:
        item.isEscaped = value.toBool();
        break;
    }

    if (tagList->setItemAt(index.row(), item)) {
        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags TagListModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable;
}

QHash<int, QByteArray> TagListModel::roleNames() const
{
    QHash<int, QByteArray> names;
    names[IdRole] = "number";
    names[TagNameRole] = "tagName";
    names[DescriptionRole] = "description";
    names[ValidRole] = "valid";
    names[EscapingRole] = "escaping";
    return names;
}

TagList *TagListModel::list() const
{
    return tagList;
}

void TagListModel::setList(TagList *value)
{
    beginResetModel();

    if (this->tagList)
        this->tagList->disconnect(this);

    tagList = value;

    if (this->tagList)
    {
        connect(this->tagList, &TagList::preNewList, this, [=]() {
            const int index = this->tagList->items().size();
            beginInsertRows(QModelIndex(), index, index);
        });
        connect(this->tagList, &TagList::postNewList, this, [=]() {
            endInsertRows();
        });
        connect(this->tagList, &TagList::preClearList, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });
        connect(this->tagList, &TagList::postClearList, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
