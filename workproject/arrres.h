#ifndef ARRRES_H
#define ARRRES_H
#include<QString>

class ArrRes
{
public:
   int arr[100][9][9]={{
       {'1',3,'x',2,'x',8,'x','x','x'},{'x',6,'x','x','x','x','x',7,4},{'x','x',4,'x',1,'x',5,'x','x'},{'x','x','x',1,6,'x',4,'x',2},{9,'x',2,8,'x','x','x',1,'x'},{6,'x',8,'x','x','x',3,'x',9},{'x',8,'x',9,'x',1,6,'x','x'},{'x','x',9,'x','x',7,'x',4,3},{7,'x','x','x',8,4,'x','x','x'}
   }};
public:
    ArrRes();
public:
    initArr();
};

#endif // ARRRES_H
