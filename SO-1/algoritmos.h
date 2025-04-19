#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#define MAX_PROCESSES 100

typedef struct {
    int id;
    double arrival_time;
    double burst_time;
    double priority;
    double deadline;
    double period;
    int queue_level;
    double waiting_time;
    double turnaround_time;
    double start_time;
    double finish_time;
    double remaining_time;
} Process;

// Declarações de funções
int load_processes_from_file(const char *filename, Process processes[], int *n);
int initialize_static_processes(Process processes[], int *n);
int input_process_details(Process processes[], int n);
void fcfs(Process processes[], int n);
void round_robin(Process processes[], int n, double time_quantum);
void sjf(Process processes[], int n);
void priority_scheduling_non_preemptive(Process processes[], int n);
void priority_scheduling_preemptive(Process processes[], int n);
void rate_monotonic(Process processes[], int n);
void earliest_deadline_first(Process processes[], int n);
void multilevel_queue_scheduling(Process processes[], int n);
void print_results(Process processes[], int n);
void calculate_statistics(Process processes[], int n);
void generate_arrival_times(Process processes[], int n, double lambda);
double generate_exponential(double lambda);
double generate_exponential_burst(double lambda);
double generate_normal_burst(double mean, double stddev);
void generate_burst_times(Process processes[], int n, double lambda, double mean, double stddev, bool use_exponential);
int generate_uniform_priority(int min_priority, int max_priority);
int generate_weighted_priority(int min_priority, int max_priority);
void assign_priorities(Process processes[], int n, int min_priority, int max_priority, bool use_weighted);
#endif