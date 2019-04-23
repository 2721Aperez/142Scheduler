#include <iostream>
#include<string>
#include<vector>
//#include<utility>
#include<algorithm>
#include<fstream>

using namespace std;
/*
.dat format 
JOB_ID       ARRIVAL_TIME       DURATION
*/
/*
For each of the above, output the following:
•Start time for each job
•Finish time for each job
•Total time elapsed for each job
•Response time for each job
Response Time = first_run - arrival
*/
bool sortcol( const vector<int>& v1, const vector<int>& v2 ) { return v1[2] > v2[2]; } 
void FIFO(vector<vector<int> >&jobs, int job_index, int job_characteristics = 3);
void BJF(vector<vector<int> >jobs, int job_index, int job_characteristics = 3 );

int main()
{
    //2D vector format:
    //where i is the ith job
    //job_list[i][0] = JOB_ID
    //job_list[i][1] = ARRIVAL_TIME
    //job_list[i][2] = DURATION
    //vector<vector<int> >job_list(100, vector<int>(3)); 
    vector<vector<int> > job_list;//This will be the list of jobs.  job_info vector will be pushed into this 2d vector.  This should be of size <=100
    vector<int> job_info(3); //This stores each job's ID, Arrival, and Duration.  It is a vector of size 3
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
    
    //FIFO(job_list, i);
    BJF(job_list, i);
    return 0;
}


    //job_list[i][0] = JOB_ID
    //job_list[i][1] = ARRIVAL_TIME
    //job_list[i][2] = DURATION
void FIFO(vector<vector<int> >&jobs, int job_index, int job_characteristics)
{
    int arrival=0;
    cout << "FIFO Scheduler" << endl;
    for(int i=0; i<job_index; i++)
    {
        cout << "Job ID: " << jobs[i][0] << "\t Elapsed Time: " << jobs[i][2] << " \t Start Time: " << arrival << "\t Finish Time: " << arrival + jobs[i][2]
             << " \t Responce Time: " << arrival - jobs[i][1] << endl << endl;
        arrival += jobs[i][2];
    }

    cout << "End of FIFO" << endl; 
}


void BJF(vector<vector<int> >jobs, int job_index, int job_characteristics)
{
    int arrival = 0;
    for(int i=0; i<job_index-1; i++)
    {
        if(jobs[i][1] == jobs[i+1][1])
        {
            int start = i, j=i;
            while(jobs[i][1] == jobs[j++][1] && j<=job_index-1);
            sort(jobs.begin()+start, jobs.begin()+j, sortcol);
        }
    }

    for(int i=0; i<job_index; i++)
    {
        cout << "Job ID: " << jobs[i][0] << "\t Elapsed Time: " << jobs[i][2] << " \t Start Time: " << arrival << "\t Finish Time: " << arrival + jobs[i][2]
             << " \t Responce Time: " << arrival - jobs[i][1] << endl << endl;
        arrival += jobs[i][2];
    }

}



    //To test the vector out
    // for(int i=0; i<job_index; i++)
    // {
    //     for(int j=0; j<job_characteristics; j++)
    //     {
    //         cout << jobs[i][j] << " ";
    //     }
    //     cout << endl;
    // }