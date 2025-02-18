#include<iostream>
#include<cstdlib>

using namespace std;

int main(int argc,char *avg[]){
    //double num[20]={};
    double sum = 0,avgs = 0;
    if (argc < 2)
    {
        cout << "Please input numbers to find average." << endl;
    }
    else{
        for (int i = 1; i < argc; i++)
        {
            double num = atof(avg[i]);
            sum += num;
            
        }
        avgs = sum/(argc-1);

        cout << "---------------------------------" << endl;
        cout << "Average of " << argc-1 << " numbers = "<< avgs << endl;
        cout << "---------------------------------" << endl;

    }
    return 0;
    
}
