#ifndef Ranking_H
#define Ranking_H

#include <QObject>
#include <QDebug>
#include <QTextStream>
#include <QList>
#include <QFile>

class Ranking : public QObject
{
  Q_OBJECT
public:
  explicit Ranking(QObject *parent = nullptr);

  bool openRank();
  void saveRank();
  void addPlayer(QString nickname, int score, int time);

signals:

private:
  int size;

  QString filepath;
  QFile * file;

  struct rank_row{
    QString nickname;
    int score;
    int time;
  };

  QList <rank_row> rank_db;

  bool parser(QString line);

};

#endif // Ranking_H
