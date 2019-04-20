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
    //2D vector format:
    //where i is the ith job
    //job_list[i][0] = JOB_ID
    //job_list[i][1] = ARRIVAL_TIME
    //job_list[i][2] = DURATION
    //vector<vector<int> >job_list(100, vector<int>(3)); 
    vector<vector<int> > job_list;//This will be the list of jobs.  job_info vector will be pushed into this 2d vector
    vector<int> job_info(3); //This stores each jobs ID Arrival and Duration
    int i=0; //Index for job_list.  Cannot be more than 100 job entries
    int j=0;//Index for the job info. There will only be 3 categories of info
    int data=0;//Temp stores each int from the .dat file
    const int JOB_CATEGORIES = 3;//There will be only 3 categories per job

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

    //Testing if reading and storing from file worked
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