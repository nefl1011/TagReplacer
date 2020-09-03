#ifndef TAGLIST_H
#define TAGLIST_H

#include <QObject>

#include "Tag.h"
#include "CheckTagComponent.h"

class TagList : public QObject
{
    Q_OBJECT
private:
    QList<Tag> itemList;
    CheckTagComponent *tagChecker;

public:
    explicit TagList(QObject *parent = nullptr);
    ~TagList();

    QList<Tag> items() const;

    /**
     * @brief setItemAt Updates the backend model.
     * @param index The index of the item to change.
     * @param item The updated item for replacement.
     * @return Item replaced old item.
     */
    bool setItemAt(int index, const Tag &item);

signals:
    /**
     * @brief preClearList Signal to start the removing rowitems of the user interface.
     * @param index Current index of the rowitem which should be removed.
     */
    void preClearList(int index);

    /**
     * @brief postClearList Signal to end the removing rowitems of the user interface.
     */
    void postClearList();

    /**
     * @brief preNewList Signal to start adding rowitems into the user interface.
     */
    void preNewList();

    /**
     * @brief postNewList Signal to end adding rowitems into the user interface.
     */
    void postNewList();

public slots:
    /**
     * @brief checkStringSlot Slot for the qml signal to check a string for valid tags.
     * @param str An input string to check if it contains a valid tag or not.
     */
    void checkStringSlot(const QString &str);

    /**
     * @brief replaceSlot Replaces every tag and refactors backslashes for the output string.
     * @return An output string for the user interface.
     */
    QString replaceSlot();
};

#endif // TAGLIST_H
