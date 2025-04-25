#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    // implementation is very similar to n-queens problem

    // setup
    int numDays = avail.size();
    int numWorkers = avail[0].size();

    // setup sched
    for(int i = 0; i < numDays; i++)
    {
        std::vector<Worker_T> daySched;
        sched.push_back(daySched);
    }

    // setup shifts
    workerShifts shifts;
    for(int i = 0; i < numWorkers; i++)
    {
        shifts.push_back(0);
    }

    // call search
    size_t day = 0;
    return search(avail, dailyNeed, maxShifts, sched, shifts, day); // initial recursive call
}

void updateMatrix(
    DailySchedule& sched,
    workerShifts& shifts,
    size_t day,
    Worker_T worker,
    int change)
{
    if(change > 0) // add worker
    {
        sched[day].push_back(worker); // update sched
        shifts[worker] += 1;
    }
    else if(change < 0) // remove worker
    {
        sched[day].pop_back();
        shifts[worker] -= 1;
    }
}


bool search(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    workerShifts& shifts,
    size_t day)
{
    if(day == avail.size()) // schedule is solved
    {
        return true;
    }

    if(sched[day].size() == dailyNeed) // day is full, skip ahead
    {
        return search(avail, dailyNeed, maxShifts, sched, shifts, day + 1); // recursive call
    }

    else
    {
        for(Worker_T w = 0; w < avail[0].size(); w++) // iterate through each worker
        {
            // if (available on this day, has an open shift, and more daily workers needed)
            if(avail[day][w] && shifts[w] < maxShifts && sched[day].size() < dailyNeed) // worker can work on this day 
            {
                updateMatrix(sched, shifts, day, w, 1); // add worker to schedule
                if(search(avail, dailyNeed, maxShifts, sched, shifts, day)) // recursive call, if true then we are done
                {
                    return true;
                } 
                // this part below only happens if search returns and doesnt work
                updateMatrix(sched, shifts, day, w, -1); // remove worker from schedule
            }
        }
        return false; // fails
    }
}

