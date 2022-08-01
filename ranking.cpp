#include "ranking.h"

Ranking::Ranking(QObject *parent)
  : QObject{parent}
{
  filepath = "rank.txt";
  size = 0;
  file = nullptr;

}

bool Ranking::openRank()
{
  file = new QFile(filepath);
  if(!file->open(QIODevice::Append | QIODevice::Text))
    {
      qDebug() << "ERROR: " + file->errorString();
      return false;
    }
  qDebug() << "File opened";

  QTextStream in(file);

  while(!in.atEnd())
    {
      QString line = in.readLine();

      if(parser(line) != true)
        {
          qDebug() << "Error while parsing file!";
        }
      else{
          qDebug() << "Parsed (OK) and add to Ranking row";
        }
    }
  return true;
}

bool Ranking::parser(QString line)
{
  //line pattern: Nickname,Score,Time;
  if(line.isEmpty() || line.isNull())
    {
      qDebug() << "Parser Error: Empty/Null line";
      return false; //unrecognized
    }

  return true; //recognized
}
