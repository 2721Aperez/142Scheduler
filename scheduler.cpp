#include <iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>
#include <sstream>


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
bool sortcol( const vector<int>& v1, const vector<int>& v2 ) { return v1[2] > v2[2]; } //For BJF
bool sortcolIncr( const vector<int>& v1, const vector<int>& v2 ) { return v1[2] < v2[2]; } //For SJF
bool sortArrival( const vector<int>& v1, const vector<int>& v2 ) { return v1[1] < v2[1]; } //Sorting by the arrival time of jobs
bool sortDuration( const vector<int>& v1, const vector<int>& v2) { return v1[3] < v2[3]; } //Sorting by duration of job
bool sortID(const vector<int>& v1, const vector<int>& v2) { return v1[0] < v2[0]; }        //Sorting by Job ID

void FIFO(vector<vector<int> >&jobs, int job_index, int job_characteristics = 3);
void BJF(vector<vector<int> >jobs, int job_index, int job_characteristics = 3 );
void SJF(vector<vector<int> >jobs, int job_index, int job_characteristics = 3); //Can be done the same way as BJF just reverse sortcol function
void RR(vector<vector<int> >jobs, int job_index, int job_characteristics = 3);
void STCF(vector<vector<int>>jobs, int job_index, int job_characteristics = 3);

int main()
{
    //2D vector format:
    //where i is the ith job
    //job_list[i][0] = JOB_ID
    //job_list[i][1] = ARRIVAL_TIME
    //job_list[i][2] = DURATION
    vector<vector<int> > job_list;//This will be the list of jobs.  job_info vector will be pushed into this 2d vector.  This should be of size <=100
    vector<int> job_info(3); //This stores each job's ID, Arrival, and Duration.  It is a vector of size 3
    int i=0; //Index for job_list.  Cannot be more than 100 job entries
    int j=0;//Index for the job info. There will only be 3 categories of info
    int data=0;//Temp stores each int from the .dat file
    const int JOB_CATEGORIES = 3;//There will be only 3 categories per job
    int jobID, arrivalTime, duration;

    ifstream jobs;
    jobs.open("Jobs.dat");
    
    string line;
    while(getline(jobs, line)) {
        istringstream iss(line);
        if(!(iss >> jobID >> arrivalTime >> duration)) {break;} //error
        job_info[0] = jobID;
        job_info[1] = arrivalTime;
        job_info[2] = duration;
        job_list.push_back(job_info);
        i++;
        if(i >= 100) {break;}   // Maximum number of jobs is 100
        
    }

    jobs.close();
    sort(job_list.begin(), job_list.end(), sortArrival);

    FIFO(job_list, i);
    BJF(job_list, i);
    SJF(job_list, i);
    STCF(job_list, i);
    RR(job_list,i);
    return 0;
}


    //job_list[i][0] = JOB_ID
    //job_list[i][1] = ARRIVAL_TIME
    //job_list[i][2] = DURATION
void FIFO(vector<vector<int> >&jobs, int job_index, int job_characteristics)
{
    int arrival=0;
    cout << "FIFO Scheduler" << endl;

    if(job_index == 0) { cout << "No jobs available. End of FIFO." << endl; return; } // Edge case: no jobs
    
    for(int i=0; i<job_index; i++)
    {
        if(jobs[i][1] > arrival) { arrival = jobs[i][1]; }
        cout << "Job ID: " << jobs[i][0] << "\t Elapsed Time: " << jobs[i][2] << " \t Start Time: " << arrival << "\t Finish Time: " << arrival + jobs[i][2]
             << " \t Response Time: " << arrival - jobs[i][1] << endl << endl;
        arrival += jobs[i][2];
    }

    cout << "End of FIFO" << endl << endl; 
}


void BJF(vector<vector<int>>jobs, int job_index, int job_characteristics)
{
    int i = 0;
    int arrival = 0;
    cout << "Biggest Job First Scheduler " << endl;

    if(job_index == 0) { cout << "No jobs available. End of BJF." << endl; return; } // Edge case: no jobs
    else if(job_index == 1) { 
        arrival += jobs[i][1];
        cout << "Job ID: " << jobs[i][0] << "\tStart Time: " << arrival << "\tFinish Time: " << 
        arrival + jobs[i][2] << "\tElapsed Time: " << jobs[i][2] << "\tResponse Time: " << jobs[i][1] - arrival << endl;
        return;
    }    

    for(; i<job_index; i++)
    {
        int index = i;

        if(index == 0 && jobs[index][1] != 0) { arrival = jobs[i][1]; }   // Increment time until first job(s) arrives

        if(jobs[index][1] > arrival) { arrival = jobs[index][1]; }

        while(jobs[index][1] <= arrival && index < job_index - 1) { // Find all jobs that have arrived at or before current time
            index++;
        }
        if(jobs[index][1] > arrival) { index--; }        
        
        sort(jobs.begin()+i, jobs.begin()+index+1, sortcol); // Sort all available jobs by biggest job first

        cout << "Job ID: " << jobs[i][0] << "\tStart Time: " << arrival << "\tFinish Time: " << arrival + jobs[i][2] <<
        "\tElapsed Time: " << jobs[i][2] << "\tResponse Time: " << arrival - jobs[i][1] << endl << endl;
        
        arrival += jobs[i][2];        
    }

    cout << "End of Biggest Job First" << endl << endl;
}

void SJF(vector<vector<int> > jobs, int job_index, int job_characteristics)
{
    int i = 0;
    int arrival = 0;
    cout << "Start of Smallest Job First" << endl;
    
    if(job_index == 0) { cout << "No jobs available. End of SJF." << endl; return; } // Edge case: no jobs
    else if(job_index == 1) { 
        arrival += jobs[i][1];
        cout << "Job ID: " << jobs[i][0] << "\tStart Time: " << arrival << "\tFinish Time: " << 
        arrival + jobs[i][2] << "\tElapsed Time: " << jobs[i][2] << "\tResponse Time: " << jobs[i][1] - arrival << endl;
        return;
    }

    for(; i<job_index; i++)
    {
        int index = i;

        if(index == 0 && jobs[index][1] != 0) { arrival = jobs[i][1]; }   // Increment time until first job(s) arrives

        if(jobs[index][1] > arrival) { arrival = jobs[index][1]; }

        while(jobs[index][1] <= arrival && index < job_index - 1) { // Find all jobs that have arrived at or before current time
            index++;
        }
        if(jobs[index][1] > arrival) { index--; }

        sort(jobs.begin()+i, jobs.begin()+index+1, sortcolIncr); // Sort all available jobs by biggest job first

        cout << "Job ID: " << jobs[i][0] << "\tStart Time: " << arrival << "\tFinish Time: " << arrival + jobs[i][2] <<
        "\tElapsed Time: " << jobs[i][2] << "\tResponse Time: " << arrival - jobs[i][1] << endl << endl;
        
        arrival += jobs[i][2];
    }

    cout << "End of Smallest Job First Scheduler" <<endl << endl;
}

void RR(vector<vector<int> >jobs, int job_index, int job_characteristics)
{
    cout << "Start of Round Robin" << endl;
    vector<int>arrival; //this vector will be the copy of arrival time
    vector<int>rem;     //this vector will be the copy of duration time
    int comp[job_index];    //this array will hold the completion time
    int st[job_index];   //this array will hold the start time of the job
    int et[job_index];  //this array will hold the elapsed time
    int t = 0;      //current time
    int q = 1;      //quantum
    
    for(int i=0; i< job_index; i++)     
    {
        arrival.push_back(jobs[i][1]);  //copy arrival time
        rem.push_back(jobs[i][2]);      //copy duration
    }
    if(job_index == 0){        //edge case when there is no job
        cout << "There's no job. Ending Round Robin" <<  endl;
        return;
    }
    if(job_index == 1){     //edge case when there is only one job
        cout << "Job ID: " << jobs[0][0] << "\t Start Time: " << jobs[0][1] << "\t Finish Time: " << jobs[0][2] + jobs[0][1] << "\t Elapsed Time: " << 
        jobs[0][2] << "\t Repsonse Time: 0" << endl;
        cout << "End of Round Robin" << endl; 
        return;
    }

    while (true) { 
            bool flag = true; 
            for (int i = 0; i < job_index; i++) { 
                if (arrival[i] <= t) { 
                    if (arrival[i] <= q) { 
                        if (rem[i] > 0) { 
                            flag = false; 
                            if (rem[i] > q) { 
                                t = t + q; 
                                rem[i] = rem[i] - q; 
                                arrival[i] = arrival[i] + q;                            
                            } 
                            else { 
                                t = t + rem[i]; 
                                comp[i] = t - jobs[i][1]; 
                                et[i] = comp[i] - jobs[i][1];
                                rem[i] = 0;
                            } 
                        } 
                    } 
                    else if (arrival[i] > q) { 
                        for (int j = 0; j < job_index; j++) { 
                            if (arrival[j] < arrival[i]) { 
                                if (rem[j] > 0) { 
                                    flag = false; 
                                    if (rem[j] > q) { 
                                        t = t + q; 
                                        rem[j] = rem[j] - q; 
                                        arrival[j] = arrival[j] + q; 
                                    } 
                                    else { 
                                        t = t + rem[j]; 
                                        comp[j] = t - jobs[j][1]; 
                                        et[j] = comp[j] - jobs[j][1];
                                        rem[j] = 0; 
                                    } 
                                } 
                            } 
                        } 
                        if (rem[i] > 0) { 
                            flag = false;  
                            if (rem[i] > q) { 
                                t = t + q; 
                                rem[i] = rem[i] - q; 
                                arrival[i] = arrival[i] + q; 
                            } 
                            else { 
                                t = t + rem[i]; 
                                comp[i] = t - jobs[i][1]; 
                                et[i] = comp[i] - jobs[i][1];
                                rem[i] = 0; 
                            } 
                        } 
                    } 
                } 
                else if (arrival[i] > t) { 
                    t++; 
                    i--; 
                } 
            } 
            // for exit the while loop 
            if (flag) { 
                break; 
            } 
        }
    for(int i = 0; i < job_index; i++) {
         cout << "Job ID: " << jobs[i][0] << "\tStart Time: " << jobs[i][1] << "\tFinish Time: " << comp[i] <<
        "\tElapsed Time: " << et[i] << "\tResponse Time: " << comp[i] - et[i] - jobs[i][1] << endl;
    }
    cout << "End of Round Robin" << endl;
}


void STCF(vector<vector<int>>jobs, int job_index, int job_characteristics) {
    int arrival = 0;
    int index = 0;
    int shortest_job_index = 0;
    vector<int>job_info(4);      // Vector to hold Job ID, Start Time, Finish Time, and Duration Remaining
    vector<vector<int>>job_list; // Vector to hold job vectors

    cout << "Start of STCF" << endl;

    if(job_index == 0) { cout << "No jobs available. End of SCTF" << endl; return;} // Edge case: no jobs
    else if(job_index == 1) {
        arrival = jobs[0][1] + jobs[0][2]; // Time after completion equal to job arrival time + job duration
        cout << "Job ID: " << jobs[0][0] << "\tStart Time: " << jobs[0][1] << "\tFinish Time: " << arrival << 
        "\tTotal Time Elapsed: " << jobs[0][2] << "\tResponse Time: 0" << endl; // Hardcoded response time, only one job so it is always 0
        return;
    }

    sort(jobs.begin(), jobs.end(), sortArrival);

    while(arrival != jobs[index][1]) {  //increment time until first job comes in
        arrival++;
    }
    
    if(arrival != jobs[index+1][1]) {
        job_info[0] = jobs[index][0];    // Job ID
        job_info[1] = jobs[index][1];    // Start Time
        job_info[2] = -1;                // Finish Time
        job_info[3] = jobs[index][2];    // Remaining duration
        job_list.push_back(job_info);
    }

    while((arrival != jobs[index+1][1]) && (job_list[index][3] != 0)) { // while next job has not come in
        arrival++;
        job_list[index][3]--;
    }

    if(job_list[index][3] == 0) {   // First job finished
        job_list[index][2] = arrival;
    }

    if(jobs[index+1][1] != arrival) { arrival = jobs[index+1][1]; } // If second job hasn't come in at completion of first job

    int temp = 0; // temp points to next job that has not arrived
    bool allJobsArrived = false;
    bool jobsComplete = false;

    if(index + 1 < job_index) // Check to see if out of bounds (not needed since we know there is more than 1?)
        temp = index + 1;

    while(!jobsComplete && !allJobsArrived) { // Keep looping until all jobs are added to jobs_list and jobs are complete
        
        if((shortest_job_index == job_list.size()-1) && (arrival < jobs[temp][1]))
            arrival = jobs[temp][1];
        
        while(temp < job_index && (jobs[temp][1] == arrival)) {
        // Add all jobs that have arrived at current time
            job_info[0] = jobs[temp][0]; // Job ID
            job_info[1] = -1;            // Start Time
            job_info[2] = -1;            // Finish Time
            job_info[3] = jobs[temp][2];
            job_list.push_back(job_info);
            index++;
            temp++;
            if(temp == job_index) {allJobsArrived = true;};
        }
        if(temp == job_index) { allJobsArrived = true; }

        shortest_job_index = 0;

        //find the shortest duration job based on all jobs that have come in
        for(int i = 0; i < job_list.size(); i++) {
            if(job_list[i][3] < job_list[shortest_job_index][3]) {
                if(job_list[i][3] > 0) {
                    shortest_job_index = i; 
                }
            }
            else if(job_list[shortest_job_index][3] == 0) {
                shortest_job_index = i;
            }
        }
        
        if(!allJobsArrived) {  // There are jobs that have not arrived
            if(job_list[shortest_job_index][1] == -1) {job_list[shortest_job_index][1] = arrival;} // If job not yet started, set start time
            
            while(arrival != jobs[temp][1] && job_list[shortest_job_index][3] > 0) {   // Run shortest job until next job(s) come in
                arrival++;
                job_list[shortest_job_index][3]--;
            }
            
            if(job_list[shortest_job_index][3] == 0) {job_list[shortest_job_index][2] = arrival;} // If job completed, record finish time
        }
        else {
            sort(job_list.begin(), job_list.end(), sortDuration);
            for(int i = 0; i < job_list.size(); i++) {
                if(job_list[i][3] != 0) {
                    if(job_list[i][1] == -1) {job_list[i][1] = arrival;}
                    arrival += job_list[i][3];
                    job_list[i][3] = 0;
                    job_list[i][2] = arrival;
                }
            }
            jobsComplete = true;
        }
    }
    
    sort(jobs.begin(), jobs.end(), sortID);
    sort(job_list.begin(), job_list.end(), sortID);

    for(int i = 0; i < job_list.size(); i++) {
        cout << "Job ID: " << job_list[i][0] << "\t Start Time: " << job_list[i][1] << "\t Finish Time: " << job_list[i][2] <<
        "\t Elapsed Time: " << job_list[i][2] - job_list[i][1] << "\t Response Time: " << job_list[i][1] - jobs[i][1] << endl << endl;
    }

    cout << "End of STCF Scheduler" << endl;
}