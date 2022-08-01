#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include <QQmlContext>

#include "clickergame.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QGuiApplication app(argc, argv);

  QQuickStyle::setStyle("Material");

  ClickerGame ClickerGameEngine;

  QQmlApplicationEngine engine;
  QQmlContext *rootContext = engine.rootContext();
  rootContext->setContextProperty("CGEngine", &ClickerGameEngine);

  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl) {
    if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);

  return app.exec();
}
