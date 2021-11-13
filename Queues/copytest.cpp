#include <iostream>

#include "config.h"

using namespace std;

#include "QueueLinked.cpp"


int main(){
  QueueLinked<int> line1;
  line1.enqueue(1);
  line1.enqueue(2);
  line1.enqueue(3);
  line1.showStructure();
  QueueLinked<int> line2(line1);
  line2.showStructure();
  QueueLinked<int> line3 = line1;
  line3.showStructure();

  return 0;
}
