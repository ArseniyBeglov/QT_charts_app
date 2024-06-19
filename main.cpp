#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "randomnumbergenerator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    RandomNumberGenerator randomNumberGenerator;
    engine.rootContext()->setContextProperty("randomNumberGenerator", &randomNumberGenerator);

    const QUrl url(QStringLiteral("qrc:/untitled3/Main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
