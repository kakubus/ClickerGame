#ifndef CLICKERGAME_H
#define CLICKERGAME_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QElapsedTimer>

#include "ranking.h"

class ClickerGame: public QObject
{
    Q_OBJECT
public:
  explicit ClickerGame(QObject *parent = nullptr);
  ~ClickerGame();

  struct position{
    int x;
    int y;
  } clicker_position;

  int primitive_time;

  QTimer *timer;
  QString dialog_header; //header text
  QString text_dialog; //text for popup dialog

  void levelManager(int gameover, int gameend, int difficult);  //0 - easy, 1- normal, 2 - hard

  Ranking GameRanking;

signals:
  void changePosition();  //change position of clicker, depends on correct click or time interval
  void levelUpdate();     //simple signal when change lvl. It shows on level info (QML) value of level
  void updateScore();
  void updateTime();
  void showDialog();      //open dialog for information for eg. Game over
  void shortInfo();       //short text information for player for eg. You reached new lvl!

public slots:
  void setNewCoordinates(bool isClicked = false); // random set coordinates clicker. isClicked means that Clicker was clicked or not. If not, generate new position and get -10 to score, if clicked only get new position
  void setNickname(QString nick);
  void timeGameScheduler(); // time counter, it use getNewCoordinates (depends on time_interval)
  void clicked(); //click on Clicker. Count score and get new coordinates

  int getXPosition();
  int getYPosition();

  QString getTimeGame();
  QString getScoreGame();
  QString getDialogHeader();
  QString getDialogText();
  QString getLevel();

//  bool getMouseCoordinates(); //unused
//  void setTimeInterval(int time); //setting other time interval. Default = 5s

  void stopGame();


private:
  int score;
  int level;
  int pts_gameover;
  int pts_gameend;
  int difficulty;
  float time_interval;

  QString nickname;

  position mouse_position; // unused


};
#endif // CLICKERGAME_H
