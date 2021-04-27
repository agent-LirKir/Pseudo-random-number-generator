#include "Generator_Random_Numbers.h"

//SEARCH TWO RELATIVELY SIMPLE NUMBERS
int RandomGenerator::NOD(int a ,int b )
  {         
       int r,c; 
     //for correct search   
       if(b>a)
          {c=b;
          b=a;
          a=c;}
      //get two relatively prime numbers 
        do
       {  
          r = a%b;
          a =  b;
          b = r; 
       }while(b!=0);

        //returning result of function work
        return a;
      }

//GENERATOR OF RUNDEM NUMBERS
int RandomGenerator::generator(int Fnn,int F)
      {   //Formula our generator
         int Number;
         Number = (a*Fnn + b*F + c) % M  ;                                                    

         return  Number ;    
      }

//SET LENGTH OF RANDOM NUMBER
void RandomGenerator::setLength(int n0)
     { M = (int) pow(2,n0);}

//SET AND RESET SEQUENCE OF RANDOM NUMBERS
void RandomGenerator::resetSequence()
    {
       a = rand()%M +1;
       b = rand()%M +1;
       c = rand()%M +1;
     //looking for two relatively prime numbers
       while(NOD(a,b)!=1 || a==b)///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
       {
          a =  rand()%M +1;
          b = rand()%M +1;
       }
     //fill up start conditions a,b,c,F0,F1,F2;
       F0 = rand()%M +1;
       F1 = rand()%M +1;
       F2= rand()%M +1;

      //filling in array 

       seriesOfNumbers[0]=F0;
       seriesOfNumbers[1]=F1;
       seriesOfNumbers[2]=F2;

    //get random series of numbers 
       for(int i = 3; i<n ; i++)
        seriesOfNumbers[i] = generator(seriesOfNumbers[i-1],seriesOfNumbers[i-3]); 
    }


//CONSTRUCTOR(by defauls arguments
RandomGenerator::RandomGenerator()
     { 
       //Set default conditions
       setLength(5);
       k = 100;
       n = 1000; 
       
       //Initialization by 0
       mathExp=0;
       disper=0;
       standardDevi=0;  
       Period = 0;
       Xsqr=0;
       p1=p2= 0;
 
       
        probabilities = new double[k];
        for(int i = 0;i<k;i++)
            probabilities[i]=0;
        
 
        seriesOfNumbers = new int[n];
        for(int i = 0;i<k;i++)
            seriesOfNumbers[i]=0; 
      
        //Set sequence of random numbers
        resetSequence();
       }

//SET LENGTH OF RANDOM NUMBER with arguments were entered by user
RandomGenerator::RandomGenerator(int n0,int k0,int t)
      {   
      //Set variables values
       setLength(t);
       k = k0;
       n = n0;

       //Initialization by 0
       mathExp=0;
       disper=0;
       standardDevi=0;  
       Period = 0;
       Xsqr=0;
       p1=p2= 0;
      
       probabilities = new double[k];
       for(int i = 0;i<k;i++)
           probabilities[i]=0;
        
 
       seriesOfNumbers = new int[n];
       for(int i = 0;i<k;i++)
           seriesOfNumbers[i]=0;
        
       //Set sequence of random numbers
       resetSequence();
      }

//DESTRUCTOR
RandomGenerator::~RandomGenerator(){delete[] seriesOfNumbers; delete[] probabilities;}
   
//GET PROBABILITIES SEQUENCE
void RandomGenerator::getProbabilies()
      {   
       double step = (double) M/k;
       double length =0;
       double  quantity = 0;

    
       for(int i=0;i < k;i++)
        {
         for(int j=0;j < n;j++)
           if((length<= seriesOfNumbers[j]) && ((length+step) > seriesOfNumbers[j]))
               quantity++;
              
           probabilities[i] = (double) quantity/n;
           quantity=0;
           length +=step;
        }
        length =0;
        quantity = 0;
      }

//TEST  disper, standardDevi, mathExp, Xaquare
void RandomGenerator:: Test()
      {   
       double sum =0;
       //Math expected
       for(int j=0;j<n;j++)
          sum+=seriesOfNumbers[j];

       mathExp=sum/n;

       sum=0;
       //Dispersion
       for(int i=0;i<n;i++)
          sum+= pow(seriesOfNumbers[i] - mathExp,2);

       disper = sum/n ;
     
       //Standard deviation
       standardDevi = pow(disper,0.5); 
       
        sum=0;
       //X^2-TEST
       //p1=5%
       double x1 = -1.64;
       p1 = n-1 + pow(2*n-2,0.5)*x1 + (double)(2/3)*x1*x1-(double)(2/3);
       ////////////////////////////////////////////////////////(20.03.18)
       //p2=75%
       double x2 = 1.64;
       p2 = n-1 + pow(2*n-2,0.5)*x2 + (double)(2/3)*x2*x2-(double)(2/3);
       //////////////////////////////////////////////////////
       for(int i =0;i<k;i++)
         sum +=k*pow((double)probabilities[i]*n,2);
         Xsqr = (double)(sum/n - n);
       
      }

//TEST OF PERIODS
double RandomGenerator::getPeriod()
      {
       int index = 2;
       int F0x;
       int F1x;
       int F2x;
       
           for(int g=3;g<n;g++)
            {  F0x =seriesOfNumbers[g-3] ;
               F1x = seriesOfNumbers[g-2];
               F2x = seriesOfNumbers[g-1];
               for(int i=g;i<n;i++)
                  if((seriesOfNumbers[i] == F2x) &&  (seriesOfNumbers[i-1] == F1x) &&  (seriesOfNumbers[i-2] == F0x))
                   {
                    index = i; 
                    break;
                   }
                  if(index != 2)
                   {
                    break;
                   }
            }   
 
              Period  = index-2;  
        return  Period;  
      }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RandomGenerator::writeIntoFile() const                                                            //CONST !!!
     { 
       using namespace std;
    //OPEN the file "Array_of_Random_numbers.txt"////////////////

     /*  ofstream writeInFile("Array_of_Random_numbers.txt"); 
       for (int i =0; i< n;i++)
       { 
         if(i==n-1)
         writeInFile << seriesOfNumbers[i];
         else 
         writeInFile << seriesOfNumbers[i] << '\n';
       }
         writeInFile.close();*/

      //OPEN file "Array_of_Probabilities.txt"/////////////////////////////

         ofstream writeInFile("Array_of_Probabilities.txt");
      for (int i =0; i< k;i++)
     { 
        if(i==k-1)
        writeInFile <<  probabilities[i] ;
        else 
        writeInFile <<  probabilities[i] << '\n';
       }
         writeInFile.close();

     }

//OUTPUT
void RandomGenerator:: output() const                                                                   //CONST !!!
    { using namespace std;
       cout<<"START CONDITIONS:"<<endl;
       cout<<"a="<<a<<endl;
       cout<<"b="<<b<<endl;
       cout<<"c="<<c<<endl;
       cout<<"F0="<<F0<<endl;
       cout<<"F1="<<F1<<endl;
       cout<<"F2="<<F2<<endl;
       cout<<"N="<<n<<endl;
       cout<<"K="<<k<<endl;
       cout<<"M(2^n)="<<M<<endl;

       if(n <= 100)
      { cout<<endl<<"Sequence of random numbers:"<<endl;
       for(int i = 0; i<n ; i++)
         cout<<i<<")"<<seriesOfNumbers[i]<<endl;}

       cout<<"Probabilities:"<<endl;
       double check=0;
       for(int i = 0; i<k ; i++)
        { check+=probabilities[i];
         cout<<i<<")"<<probabilities[i]<<endl;
        }
          
        cout<<"Test:"<<check<<endl;
        cout<<"Math expected = "<<mathExp<<endl;
        cout<<"Dispersion = "<<disper<<endl;
        cout<<"Standard deviation = "<<standardDevi <<endl;
        cout<<"Period:"<<Period<<endl;
        cout<<"X-square test:"<<Xsqr<<endl;
        cout<<"p1 = 5%: X-squareTheor = "<<p1<<endl;
        cout<<"p2 = 95%: X-squareTheor = "<<p2<<endl;
        cout<<endl;
    }


