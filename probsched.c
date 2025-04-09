#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_PROCESSES 100

typedef struct {
    int id;
    double arrival_time;
    double burst_time;
    double priority;
    double start_time;
    double finish_time;
    double turnaround_time;
    double waiting_time;
} Process;

void generate_processes(Process processes[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].arrival_time = (double)rand() / RAND_MAX * 10;  // Poisson-like arrival
        processes[i].burst_time = (double)rand() / RAND_MAX * 5 + 1;  // Exponential burst time
        processes[i].priority = rand() % 10 + 1;  // Random priority
    }
}

void fcfs(Process processes[], int n) {
    double current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].start_time = current_time;
        processes[i].finish_time = current_time + processes[i].burst_time;
        processes[i].turnaround_time = processes[i].finish_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].start_time - processes[i].arrival_time;
        current_time += processes[i].burst_time;
    }
}

void print_results(Process processes[], int n) {
    double total_turnaround = 0, total_waiting = 0;
    printf("ID  Arrival  Burst  Start  Finish  Turnaround  Waiting\n");
    for (int i = 0; i < n; i++) {
        printf("%2d  %7.2f  %5.2f  %5.2f  %6.2f  %10.2f  %7.2f\n",
               processes[i].id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].start_time, processes[i].finish_time,
               processes[i].turnaround_time, processes[i].waiting_time);
        total_turnaround += processes[i].turnaround_time;
        total_waiting += processes[i].waiting_time;
    }
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", total_waiting / n);
}
/**
 * Função para calcular estatísticas relacionadas aos processos.
 * 
 * @param processes Array de estruturas de processos contendo informações sobre cada processo.
 * @param n Número total de processos no array.
 * 
 * Esta função calcula as seguintes estatísticas:
 * - Tempo médio de espera (Average Waiting Time).
 * - Tempo médio de retorno (Average Turnaround Time).
 * - Utilização da CPU (CPU Utilization).
 * - Taxa de transferência (Throughput), ou seja, número de processos concluídos por unidade de tempo.
 * - Número de prazos perdidos (Dead Line Misses) em algoritmos de tempo real.
 */
void calculate_statistics(Process processes[], int n) {
    double total_turnaround = 0, total_waiting = 0, total_idle_time = 0;
    double throughput, cpu_utilization;
    int deadline_misses = 0;
    double simulation_time = processes[n - 1].finish_time;

    // Calcula o tempo total de turnaround e espera
    for (int i = 0; i < n; i++) {
        total_turnaround += processes[i].turnaround_time;
        total_waiting += processes[i].waiting_time;

        // Verifica se o processo perdeu o prazo (exemplo: prazo arbitrário de 10 unidades de tempo)
        if (processes[i].finish_time > processes[i].arrival_time + 10) {
            deadline_misses++;
        }
    }

    // Calcula o tempo ocioso total da CPU
    for (int i = 1; i < n; i++) {
        if (processes[i].arrival_time > processes[i - 1].finish_time) {
            total_idle_time += processes[i].arrival_time - processes[i - 1].finish_time;
        }
    }

    // Calcula a utilização da CPU
    cpu_utilization = ((simulation_time - total_idle_time) / simulation_time) * 100;

    // Calcula o throughput (número de processos concluídos por unidade de tempo)
    throughput = n / simulation_time;

    // Exibe as estatísticas
    printf("\nEstatísticas:\n");
    printf("Tempo médio de Turnaround: %.2f\n", total_turnaround / n);
    printf("Tempo médio de Espera: %.2f\n", total_waiting / n);
    printf("Utilização da CPU: %.2f%%\n", cpu_utilization);
    printf("Throughput: %.2f processos por unidade de tempo\n", throughput);
    printf("Perdas de Prazo: %d\n", deadline_misses);
}
int main() {
    Process processes[MAX_PROCESSES];
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    generate_processes(processes, n);
    fcfs(processes, n);
    print_results(processes, n);
    calculate_statistics(processes, n); //chamada para exibir as estatísticas
    return 0;
}
