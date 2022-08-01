#ifndef RANKING_H
#define RANKING_H

#include <QObject>
#include <QList>
#include <QFile>

class ranking : public QObject
{
  Q_OBJECT
public:
  explicit ranking(QObject *parent = nullptr);

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

  bool parser();

};

#endif // RANKING_H
