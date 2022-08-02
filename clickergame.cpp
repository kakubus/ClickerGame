#include "clickergame.h"
#include <math.h>
#include <QTimer>

#include <QDebug>
ClickerGame::ClickerGame(QObject *parent)
  : QObject{parent}
{
  timer = new QTimer(this);
  score = 0;
  level = 1;
  time_interval= 2;
  clicker_position.x = 0;
  clicker_position.y = 0;
  mouse_position.x = 0;
  mouse_position.y = 0;
  primitive_time = 0;
  pts_gameover = -50;
  pts_gameend = 400;
  difficulty = 1;
  nickname = "Player";

  GameRanking.openRank();

}

ClickerGame::~ClickerGame()
{
  timer->stop();
  GameRanking.closeRank();
}

void ClickerGame::levelManager(int gameover, int gameend, int difficult)
{
  if(score > 100)
  {
    time_interval = difficult;
  ////  text_dialog = "Level 2";
    level = 2;
    emit levelUpdate();
  }
  if(score > 300)
  {
   //// text_dialog = "Level 3";
    level = 3;
    time_interval = difficult/1.2;
    emit levelUpdate();
  }

  if(score >= gameend){
      timer -> stop();
      dialog_header = "Win!"; //header text
      text_dialog = "Excellent game! \nYour points: " + QString::number(gameend)+ "\nTime: " + getTimeGame()+"s";

      emit showDialog();
    }
  if(score <= gameover)
  {
    timer -> stop();
    dialog_header = "Game over!"; //header text
    text_dialog = "You was too slow! \nYour points: " + QString::number(gameover) + "\nTime: " + getTimeGame()+"s";

    emit showDialog();
  }
}

void ClickerGame::setNewCoordinates(bool isClicked)
{
  static int counter = time_interval*10;
  static int counter_time = 0;

  if((counter ==round(time_interval*10)) || (isClicked == true)) //counter is increased every 1s
  {
    counter = 0;
    this->clicker_position.x = rand() % (800-50) + 0;
    this->clicker_position.y = rand() % (600-50) + 0;

    qDebug() << text_dialog;

    emit updateScore();
    emit shortInfo();

    if(isClicked == false)
    {
     // text_dialog = "Ops..";
      qDebug() << text_dialog;

      score -= 10;
      emit shortInfo();
    }
    else{ //isClicked == true
        text_dialog = "Yeah! Hit!";
        counter = 0;
    }

    qDebug()<<"Time has come.. " << counter << " | " << clicker_position.x << " " << clicker_position.y;


    levelManager(pts_gameover, pts_gameend, difficulty); //Game stop at -50 points, end at 400 points and level of game is "Normal" (1)

    emit changePosition();
  }
  else{
      counter++;
      qDebug()<<counter;
  }
  if(counter_time == 10) //timer 100ms, so 10*100ms = 1s.
    {
      primitive_time++;
      counter_time = 0;
       text_dialog = "Hit icon";
           emit shortInfo();
      emit updateTime();
      emit updateScore();
    }
  counter_time++;
 // text_dialog = "Hit icon";
      emit shortInfo();


}

void ClickerGame::setNickname(QString nick)
{
  if(nick == ""| nick == " ") //temp || to do - regular exp.
  {
    nickname = "Player";
  }
  else{
    nickname = nick;
  }

  qDebug()<< "Received nickname: " + nickname;
}

void ClickerGame::timeGameScheduler()
{
  connect(timer, SIGNAL(timeout()), this, SLOT(setNewCoordinates()));
  timer->start(100); //master timer (100ms)
  emit changePosition();
}

void ClickerGame::clicked()
{
  this->score += 10;
  setNewCoordinates(true);
  //emit updateScore();
}

int ClickerGame::getXPosition()
{
  return clicker_position.x;
}

int ClickerGame::getYPosition()
{
  return clicker_position.y;
}

QString ClickerGame::getTimeGame()
{
  return QString::number(this->primitive_time);
}

QString ClickerGame::getScoreGame()
{
  return QString::number(this->score);
}

QString ClickerGame::getDialogHeader()
{
  return dialog_header;
}

QString ClickerGame::getDialogText()
{
  return text_dialog;
}

QString ClickerGame::getLevel()
{
  return "Level "+QString::number(level);
}

void ClickerGame::stopGame()
{
  timer->stop();
 // delete ClickerGame;
}


