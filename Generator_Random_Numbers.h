#include<stdlib.h>
#include<iostream>
#include<ctime>
#include<cmath>
#include<iostream>
#include <fstream>
class RandomGenerator
{  
      private:
              int M ;
              int k;
              int n;

              int a;
              int b;
              int c;

              int F0;
              int F1;
              int F2;


              double mathExp;
              double disper;
              double standardDevi;
              double Period ;
              double Xsqr;
              double p1,p2;
              
              int* seriesOfNumbers;
              double* probabilities;
              //methods
              int NOD(int,int);
              int generator(int,int);
              


              
      public:
             RandomGenerator(int,int,int);
             RandomGenerator();
             ~RandomGenerator();
             void resetSequence();
              void getProbabilies();
              void output() const;                //CONST !!!
              void writeIntoFile() const ;  //CONST !!!
              void Test();
              void Xsquare();
              void setLength(int); 
              double getPeriod();          
};
