#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <vector>

#include "DES_Layer.h"
#include "Scheduler.h"

using namespace std;

int v_flag = 0;
int e_flag = 0;

/* function */
void check_flag(int argc, char** argv, string& s_value);
void get_process(char* filename, int& max_prio, int& ofs, vector<int>& randvals, list<Process*>& process_list, DES_Layer* des_layer);
vector<int> get_randvals(char* filename);
int get_random(int& max, int& ofs, vector<int>& randvals);
void simulation(Scheduler* scheduler, DES_Layer* des_layer);
Scheduler* getScheduler(string& s_value);

/* program starts from here */
int main(int argc, char* argv[])
{
    string s_value = " ";
    vector<int> randvals;
    DES_Layer* des_layer;
    Scheduler* scheduler;
    int ofs = -1;
    int max_prio = 4;
    list<Process*> process_list;

    // invocation
    check_flag(argc, argv, s_value);

    // random number file
    randvals = get_randvals(argv[argc - 1]);

    // initialize
    des_layer = new DES_Layer();
    scheduler = getScheduler(s_value);

    // readfile and create process
    get_process(argv[argc - 2], max_prio, ofs, randvals, process_list, des_layer);

    if (e_flag == 1) {
        des_layer->show_event_q();
    }

    // start simulation
    simulation(scheduler, des_layer);
}

void simulation(Scheduler* scheduler, DES_Layer* des_layer)
{
    int current_time = 0, prev_state_time = 0;
    bool call_scheduler;
    Event* evt;
    while (true) {
        evt = des_layer->get_event();

        if (evt == nullptr) {
            break;
        }

        Process* proc = evt->get_process();
        current_time = evt->get_timestamp();
        prev_state_time = current_time - proc->get_event_time();

        switch (evt->get_transition()) {
        case 1:
            // created -> ready
            call_scheduler = true;
            break;
        case 2:
            // ready -> running
            break;
        case 3:
            // running -> blocked
            call_scheduler = true;
            break;
        case 4:
            // blocked -> ready
            call_scheduler = true;
            break;
        case 5:
            // running -> ready
            call_scheduler = true;
            break;
        }

        if (call_scheduler) {
            if (des_layer->get_next_event_time() == current_time) {
                continue;
            }
            call_scheduler = false;
            /*
            if (current_running_process == nullptr) {
              current_running_process = scheduler->get_next_process();
              if (current_running_process == nullptr) {
                continue;
              }
            }
            */
        }
    }
}

Scheduler* getScheduler(string& s_value)
{
    if (s_value == "F") {
        return new FCFS_Scheduler();
    }

    return nullptr;
}

void get_process(char* filename, int& max_prio, int& ofs, vector<int>& randvals, list<Process*>& process_list, DES_Layer* des_layer)
{
    ifstream infile(filename);

    int num = 0;
    int AT, TC, CB, IO;

    while (infile >> AT >> TC >> CB >> IO) {
        /* create process */
        Process* p = new Process(num, AT, TC, CB, IO);
        p->set_prio(get_random(max_prio, ofs, randvals));

        cout << p->get_pid() << " " << p->get_prio() << " " << endl;
        process_list.push_back(p);

        /* create event */
        Event* e = new Event(p->get_event_time(), p, 1);

        /* add to DES_Layer */
        des_layer->add_event(e);
        num++;
    }
}

int get_random(int& max, int& ofs, vector<int>& randvals)
{
    ofs++;

    if (ofs >= randvals.size()) {
        ofs = 0;
    }

    return 1 + (randvals[ofs] % max);
}

vector<int> get_randvals(char* filename)
{
    ifstream infile(filename);
    int num;

    infile >> num;
    vector<int> randvals;

    while (infile >> num) {
        randvals.push_back(num);
    }

    return randvals;
}

void check_flag(int argc, char* argv[], string& s_value)
{
    // check flag
    int index;
    int c;
    opterr = 0;

    while ((c = getopt(argc, argv, "ves:")) != -1)
        switch (c) {
        case 'v':
            v_flag = 1;
            break;
        case 'e':
            e_flag = 1;
            break;
        case 's':
            s_value = string(optarg);
            break;
        default:
            abort();
        }
}