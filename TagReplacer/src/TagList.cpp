#include "TagList.h"

TagList::TagList(QObject *parent) : QObject(parent)
{
    this->tagChecker = new CheckTagComponent();
}

TagList::~TagList()
{
    delete this->tagChecker;
}

QList<Tag> TagList::items() const
{
    return itemList;
}

bool TagList::setItemAt(int index, const Tag &item)
{
    if (index < 0 || index >= itemList.size())
    {
        return false;
    }
    const Tag &oldTag = itemList.at(index);
    if (!QString::compare(item.tag, oldTag.errorMessage, Qt::CaseSensitive))
    {
        itemList.replace(index, item);
        return true;
    }
    itemList.replace(index, item);
    return true;
}

void TagList::checkStringSlot(const QString &str)
{
    for (int i = this->itemList.size() - 1; i >= 0; i--)
    {
        emit preClearList(i);
        this->itemList.removeLast();
        emit postClearList();
    }

    QList<Tag> newList = this->tagChecker->checkInputText(str);

    for (int i = 0; i < newList.size(); i++)
    {
        emit preNewList();
        this->itemList.append(newList.at(i));
        emit postNewList();
    }
}

QString TagList::replaceSlot()
{
    QString output = QString("");

    int splittedInputSize = this->tagChecker->getSplittedInput().size();

    if (splittedInputSize == 0)
    {
        return QString("");
    }

    for (int i = 0; i < splittedInputSize - 1; i++)
    {
        output.append(this->tagChecker->getSplittedInput().at(i));
        Tag item = this->itemList.at(i);
        if (!item.isValid || item.isEscaped)
        {
            output.append("{" + item.tag + "}");
        }
        else
        {
            output.append(item.errorMessage);
        }

    }

    output.append(this->tagChecker->getSplittedInput().at(splittedInputSize - 1));

    return output;
}

