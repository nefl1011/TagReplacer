#ifndef CHECKTAGCOMPONENT_H
#define CHECKTAGCOMPONENT_H

#include <QObject>
#include <QRegularExpression>

#include "Tag.h"

class CheckTagComponent
{
private:
    QString *currentInputField;
    QStringList splittedInput;
    QRegularExpression *regexpWithErrors;
    QRegularExpression *regexp;

    /**
     * @brief isEscapedTag Method to check if a tag has a backslash in front of it. Further backslashes are considered.
     * @param tag The Tag to check for escaping chars.
     * @return Tag starts with an escaping char.
     */
    bool isEscapedTag(Tag tag);

    /**
     * @brief getErrorMessage Method to transfer message strings from valid or escaped tags.
     * @param tag The Tag to assign the message string.
     * @return The message string.
     */
    QString getErrorMessage(Tag tag);

    /**
     * @brief convertInput
     * @param input
     * @return
     */
    QString convertInput(QString input);


public:
    CheckTagComponent();
    ~CheckTagComponent();

    /**
     * @brief checkInputText Checks the input string for valid tags. Non valid tags are considered as well.
     * @param str The input string to check for tags.
     * @return A list of detected tags.
     */
    QList<Tag> &checkInputText(const QString &str);

    /**
     * @brief getSplittedInput Getter for the splitted inputstring which aren't tags.
     * @return A string list of strings without any tags.
     */
    QStringList getSplittedInput() const;
};

#endif // CHECKTAGCOMPONENT_H
