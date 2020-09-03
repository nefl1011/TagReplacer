#ifndef TagListModel_H
#define TagListModel_H

#include <QAbstractListModel>

class TagList;

class TagListModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(TagList *list READ list WRITE setList)

public:
    explicit TagListModel(QObject *parent = nullptr);

    enum
    {
        IdRole = Qt::UserRole,
        TagNameRole,
        DescriptionRole,
        ValidRole,
        EscapingRole
    };

    /**
     * @brief rowCount Returns the number of rows under the given parent.
     * @param parent
     * @return
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief data Returns the data stored under the given role for the item referred to by the index.
     * @param index
     * @param role
     * @return
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief setData Sets the role data for the item at index to value.
     * @param index
     * @param value
     * @param role
     * @return Returns true if successful; otherwise returns false.
     */
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    /**
     * @brief flags Returns the item flags for the given index.
     * @param index
     * @return
     */
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    /**
     * @brief roleNames Returns the model's role names.
     * @return
     */
    virtual QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief list QML-Getter for the tag list.
     * @return Backend tag list.
     */
    TagList *list() const;

    /**
     * @brief setList QML-Setter for the tag list.
     * @param value Edited tag list.
     */
    void setList(TagList *value);

private:
    TagList *tagList;
};

#endif // TagListModel_H
