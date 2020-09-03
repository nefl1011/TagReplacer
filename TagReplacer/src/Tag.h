#ifndef TAG_H
#define TAG_H

#include <QObject>

struct Tag
{
    int id;
    QString tag;
    int tagPosition;
    bool isValid;
    bool isEscaped;
    QString errorMessage;
};
#endif // TAG_H
