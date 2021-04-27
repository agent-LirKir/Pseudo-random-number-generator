#include"functions_GRN.cpp"
using namespace std;
 int main() 
   {

      int N = 0;
      int K = 0;
      int n = 0;
      //Input of N and M
      while(N<=0 || K<=0 || n<=0)
      {
      cout<<"Enter a N for sequence random numbers(N>3):";
      cin>>N;
      cout<<"Enter a K for sequence random numbers(K<<N|K=1:20):";
      cin>>K;
      cout<<"Enter a n for length random numbers(2^n|n=[1:10]):";
      cin>>n;
      if(N<=0)
      cout<<endl<<"Error!N<=0."<<endl;
      else if(K<=0)
      cout<<endl<<"Error!K<=0."<<endl;
      else if (n<=0)
      cout<<endl<<"Error!n<=0."<<endl;
      }
      //srand(time(0));     //////////!!!!!!!!!!!!!!!!
    

      double periods[10];
      double averagePeriod=0;
      RandomGenerator random = RandomGenerator(N,K,n);

//PERIODS TEST
      for(int g =1;g<=10;g++)
       { 
          random.setLength(g);        
        
          for(int i =0;i<10;i++)
          {
           random.resetSequence();
           averagePeriod+= random.getPeriod();
          }
         averagePeriod /=10;
         periods[g-1] = averagePeriod;
         averagePeriod= 0;
       }
//Output  
      cout<<"Periods(n=1:10):"<<endl;
      for(int i =0;i<10;i++)
       cout<<i<<")"<<periods[i]<<endl;
//Write into  Array_of_PERIODS.txt    
    ofstream write("Array_of_PERIODS.txt"); 
       for (int i =0; i< 10;i++)
       { 
         if(i==9)
         write <<periods[i];
         else 
         write << periods[i] << '\n';
       }
         write.close();
//PROBABILITIES(frequency) TEST (dispersion,math expectation,standard deviation)
  //Set length of number (M=2^n) equvalent n was entered by user
       random.setLength(n); 
       random.resetSequence();
       random.getProbabilies();
       random.getPeriod();
       random.Test();
       random.writeIntoFile();
       random.output();
      // system("pause");
          
    }


