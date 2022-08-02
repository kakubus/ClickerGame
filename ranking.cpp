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
  if(!file->open(QIODevice::ReadWrite | QIODevice::Text))
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
          qDebug() << "Error while parsing file!";
      else
          qDebug() << "Parsed (OK) and add to Ranking row";
    }
  return true;
}

void Ranking::closeRank()
{
  qDebug() << "File closed";
  file->close();
}

void Ranking::saveRank()
{
  file->flush();
}

void Ranking::addPlayer(QString nickname, int score, QString time)
{
  QTextStream out(file);
  out << nickname << "," << QString::number(score) <<"," << time <<"\n";
}

QString Ranking::showRank()
{
  QString temp = "<table style='width: 100%'>"
                 "<tr>"
                 "<th style = 'padding: 5px'>Player name</th>"
                 "<th style = 'padding: 5px'>Score</th>"
                 "<th style = 'padding: 5px'>Time [s]</th>"
                 "</tr>";
  for(int i = 0; i < rank_db.size(); i++)
    {
      temp.append("<tr>"
                  "<td style = 'padding: 5px'>"+ rank_db[i].nickname +"</td>"
                  "<td style = 'padding: 5px'>"+ QString::number(rank_db[i].score) +"</td>"
                  "<td style = 'padding: 5px'>"+ QString::number(rank_db[i].time) +"</td>"
                  "</tr>");
    }
  temp.append("</table>");
  return temp;
}

bool Ranking::parser(QString line)
{
  //line pattern: Nickname,Score,Time
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

      return true; //recognized
    }
}
