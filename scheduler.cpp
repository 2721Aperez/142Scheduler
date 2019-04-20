#include <iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;
/*
.dat format 
JOB_ID       ARRIVAL_TIME       DURATION
*/
int main()
{
    //Creates a vector of size 100 with each element will be a vector of size 3
    //Outer vector of size 100 will be for the entire list of jobs
    //Inner vector of size 3 will be formatted as follows:
    //job_list[i][0] = JOB_ID
    //job_list[i][1] = ARRIVAL_TIME
    //job_list[i][2] = DURATION
    //vector<vector<int> >job_list(100, vector<int>(3)); 
    vector<vector<int> > job_list;
    vector<int> job_info(3);
    int i=0;
    int j=0;
    int data=0;
    const int job_categories = 3;
    ifstream jobs;
    jobs.open("Jobs.dat");

    while(!jobs.eof())
    {
        while(j<3)
        {
            jobs >> data;
            job_info[j++] = data;
        }
        job_list.push_back(job_info);
        i++;
        if(j == 3){j =0;}
        if(i == 100){break;}
    }

    //Testing Reading from file
    for(int inner=0; inner < i; inner++)
    {
        for(int outter=0; outter < 3; outter++)
        {
            cout << job_list[inner][outter] << " ";
        }
        cout << endl;
    }
    return 0;
}