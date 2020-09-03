#include "CheckTagComponent.h"

CheckTagComponent::CheckTagComponent()
{
    this->currentInputField = new QString("");
    this->regexpWithErrors = new QRegularExpression("(\\\\?){[^{}]*}");
    this->regexp = new QRegularExpression("(\\\\?){([a-z]|[A-Z])\\w*}");
}

CheckTagComponent::~CheckTagComponent()
{
    delete this->currentInputField;
    delete this->regexpWithErrors;
    delete this->regexp;
}

QStringList CheckTagComponent::getSplittedInput() const
{
    return splittedInput;
}

bool CheckTagComponent::isEscapedTag(Tag tag)
{
    if (this->currentInputField->at(tag.tagPosition) == QChar('\\'))
    {
        if (tag.tagPosition == 0)
        {
            return true;
        }

        int backslashAmount = 0;
        for (int i = tag.tagPosition - 1; i >= 0; i--)
        {
            if (this->currentInputField->at(i) == QChar('\\'))
            {
                backslashAmount++;
            }
            else
            {
                break;
            }
        }
        return backslashAmount % 2 == 0;
    }
    return false;
}

QString CheckTagComponent::getErrorMessage(Tag tag)
{
    QString errorMessage = "{" + tag.tag + "}";

    if (tag.isEscaped)
    {
        errorMessage = "Escaped tag. Tag cannot be replaced.";
    }

    if (!tag.isValid)
    {
        errorMessage = "Invalid tag!";
        QRegularExpression reDigit = QRegularExpression("^\\d\\w*");
        QRegularExpression reUnderscore = QRegularExpression("^_\\w*");

        if (reDigit.match(tag.tag).hasMatch())
        {
            errorMessage = "Tag starts with a digit!";
        }
        else if (reUnderscore.match(tag.tag).hasMatch())
        {
            errorMessage = "Tag starts with an underscore (_)!";
        }
    }

    return errorMessage;
}

QList<Tag> &CheckTagComponent::checkInputText(const QString &str)
{
    this->currentInputField = new QString(str);
    QList<Tag> *tagList = new QList<Tag>();

    QRegularExpressionMatchIterator iterator = regexpWithErrors->globalMatch(str);

    for (int i = 0; iterator.hasNext(); i++) {
        QRegularExpressionMatch match = iterator.next();

        Tag currentTag = Tag();
        currentTag.id = i;
        currentTag.tagPosition = match.capturedStart();
        currentTag.isValid = regexp->match(match.captured()).hasMatch();
        currentTag.isEscaped = this->isEscapedTag(currentTag);

        if (match.captured().at(0) == QChar('\\'))
        {
            currentTag.tag = match.captured().mid(2, match.captured().length() - 3);
        }
        else
        {
            currentTag.tag = match.captured().mid(1, match.captured().length() - 2);
        }
        currentTag.errorMessage = this->getErrorMessage(currentTag);

        tagList->append(currentTag);

    }
    this->splittedInput = this->currentInputField->split(QRegularExpression("{[^{}]*}"));

    for (int i = 0; i < this->splittedInput.size(); i++)
    {
        QString splitString = this->splittedInput.at(i);
        this->splittedInput.replace(i, this->convertInput(splitString));
    }

    return *tagList;
}

QString CheckTagComponent::convertInput(QString input)
{
    QString newInput = input;
    for (int i = newInput.size() - 1; i >= 0; i--)
    {
        if (newInput.at(i) == QChar('\\'))
        {
            int backslashAmount = 0;
            int lastCursorPosition = i;
            for (int j = lastCursorPosition; j >= 0; j--)
            {
                if (newInput.at(j) == QChar('\\'))
                {
                    backslashAmount++;
                }
                else
                {
                    break;
                }
                i--;
            }
            if (backslashAmount % 2 != 0)
            {
                newInput.remove(lastCursorPosition, 1);
            }
        }
    }

    newInput.replace(QString("\\\\"), QString("\\"));

    return newInput;
}
