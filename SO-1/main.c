#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "algoritmos.h"

// Função principal
int main() {
    srand(time(NULL)); // Seed the random number generator
    Process processes[MAX_PROCESSES];
    int n, choice, input_choice;
    double time_quantum;
    double lambda = 0.5; // Rate parameter for Exponential distribution

    // Solicita ao usuário que escolha o algoritmo de escalonamento
    printf("Select Scheduling Algorithm:\n");
    printf("1. First Come First Serve (FCFS)\n");
    printf("2. Round Robin (RR)\n");
    printf("3. Shortest Job First (SJF)\n");
    printf("4. Priority Scheduling (Non-Preemptive)\n");
    printf("5. Priority Scheduling (Preemptive)\n");
    printf("6. Rate Monotonic (RM)\n");
    printf("7. Earliest Deadline First (EDF)\n");
    printf("8. Multilevel Queue Scheduling\n");
    printf("Enter your choice: ");
    if (scanf("%d", &choice) != 1 || (choice < 1 || choice > 8)) {
        fprintf(stderr, "Erro: Escolha inválida de algoritmo.\n");
        return 1;
    }

    // Solicita ao usuário o tipo de entrada
    printf("Select Input Type:\n");
    printf("1. Static List of Processes (from file)\n");
    printf("2. Manual Input of Processes\n");
    printf("Enter your choice: ");
    if (scanf("%d", &input_choice) != 1 || (input_choice < 1 || input_choice > 2)) {
        fprintf(stderr, "Erro: Escolha inválida de tipo de entrada.\n");
        return 1;
    }

    // Lida com o tipo de entrada
    if (input_choice == 1) {
        if (load_processes_from_file("lista_estatica.txt", processes, &n) != 0) {
            return 1;
        }
    } else if (input_choice == 2) {
        printf("Enter the number of processes: ");
        if (scanf("%d", &n) != 1 || n <= 0 || n > MAX_PROCESSES) {
            fprintf(stderr, "Erro: Número inválido de processos.\n");
            return 1;
        }
        if (input_process_details(processes, n) != 0) {
            return 1;
        }
    }

  

    // Solicita o time quantum se o algoritmo escolhido for Round Robin
    if (choice == 2) {
        printf("Enter time quantum for Round Robin: ");
        if (scanf("%lf", &time_quantum) != 1 || time_quantum <= 0) {
            fprintf(stderr, "Erro: Time quantum inválido.\n");
            return 1;
        }
    }

    
   
    

    // Executa o algoritmo escolhido com base na entrada do usuário
    printf("\nSimulating...\n");
    switch (choice) {
        case 1:
            fcfs(processes, n);
            break;
        case 2:
            round_robin(processes, n, time_quantum);
            break;
        case 3:
            sjf(processes, n);
            break;
        case 4:
            priority_scheduling_non_preemptive(processes, n);
            break;
        case 5:
            priority_scheduling_preemptive(processes, n);
            break;
        case 6:
            rate_monotonic(processes, n);
            break;
        case 7:
            earliest_deadline_first(processes, n);
            break;
        case 8:
            multilevel_queue_scheduling(processes, n);
            break;
        default:
            fprintf(stderr, "Erro: Algoritmo inválido.\n");
            return 1;
    }

    // Exibe os resultados dos processos
    print_results(processes, n);

    // Calcula e exibe as estatísticas dos processos
    calculate_statistics(processes, n);

    // Gera tempos de chegada com base na distribuição Exponencial
    generate_arrival_times(processes, n, lambda);

    // Exibe os tempos de chegada gerados
    printf("\nGenerated Arrival Times:\n");
      for (int i = 0; i < n; i++) {
          printf("Process %d: Arrival Time = %.2f\n", i + 1, processes[i].arrival_time);
      }

       // Gera tempos de burst com base na escolha do usuário
    printf("Select Burst Time Distribution:\n");
    printf("1. Exponential Distribution\n");
    printf("2. Normal Distribution\n");
    printf("Enter your choice: ");
    int burst_choice;
    if (scanf("%d", &burst_choice) != 1 || (burst_choice < 1 || burst_choice > 2)) {
        fprintf(stderr, "Erro: Escolha inválida de distribuição.\n");
        return 1;
    }

    if (burst_choice == 1) {
        generate_burst_times(processes, n, lambda, 0, 0, true); // Exponencial
    } else if (burst_choice == 2) {
        double mean, stddev;
        printf("Enter mean for Normal Distribution: ");
        if (scanf("%lf", &mean) != 1 || mean <= 0) {
            fprintf(stderr, "Erro: Média inválida.\n");
            return 1;
        }
        printf("Enter standard deviation for Normal Distribution: ");
        if (scanf("%lf", &stddev) != 1 || stddev <= 0) {
            fprintf(stderr, "Erro: Desvio padrão inválido.\n");
            return 1;
        }
        generate_burst_times(processes, n, 0, mean, stddev, false); // Normal
    }

    // Exibe os tempos de burst gerados
    printf("\nGenerated Burst Times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: Burst Time = %.2f\n", i + 1, processes[i].burst_time);
    }

    // Solicita ao usuário o método de atribuição de prioridades
    printf("Select Priority Assignment Method:\n");
    printf("1. Uniform Distribution\n");
    printf("2. Weighted Random Sampling\n");
    printf("Enter your choice: ");
    int priority_choice;
    if (scanf("%d", &priority_choice) != 1 || (priority_choice < 1 || priority_choice > 2)) {
        fprintf(stderr, "Erro: Escolha inválida de método de prioridade.\n");
        return 1;
    }

    // Define os limites de prioridade
    int min_priority = 1, max_priority = 10; // Exemplo: prioridades de 1 a 10

    // Atribui prioridades aos processos
    if (priority_choice == 1) {
        assign_priorities(processes, n, min_priority, max_priority, false); // Distribuição uniforme
    } else if (priority_choice == 2) {
        assign_priorities(processes, n, min_priority, max_priority, true); // Amostragem ponderada
    }

    // Exibe as prioridades atribuídas
    printf("\nAssigned Priorities:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: Priority = %f\n", i + 1, processes[i].priority);
    }


    return 0;
}
