#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TagListModel.h"
#include "TagList.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    qmlRegisterType<TagListModel>("TagList", 1, 0, "TagListModel");
    qmlRegisterUncreatableType<TagList>("TagList", 1, 0, "TagList",
                                        QStringLiteral("TagList should not be created in QML"));

    TagList tagList;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty(QStringLiteral("tagList"), &tagList);
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
