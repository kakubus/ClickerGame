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

void Ranking::closeRank()
{
  qDebug() << "File closed";
  file->close();
}

bool Ranking::parser(QString line)
{
  //line pattern: Nickname,Score,Time;
  if(line.isEmpty() || line.isNull())
    {
      qDebug() << "Parser Error: Empty/Null line";
      return false; //unrecognized
    }
  else{
      QStringList temp = line.split(",");
      if(temp.size()<3)
        {
          qDebug() << "Parser Error: Not recognized 3 variables";
          return false; //unrecognized
        }
      //                  nickname, score,  time
      rank_row temp_row = {temp[0], temp[1].toInt(), temp[2].toInt()};
      rank_db.append(temp_row);
      qDebug()<< "1: " << temp_row.nickname<< "2: " << temp_row.score <<"3: " << temp_row.time;

//      for(int i = 0; i<temp.size(); i++)
//        {


//        }
        return true; //recognized
    }


}
