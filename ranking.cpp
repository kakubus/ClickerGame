#include "ranking.h"

ranking::ranking(QObject *parent)
  : QObject{parent}
{
  filepath = "rank.txt";
  size = 0;

}
