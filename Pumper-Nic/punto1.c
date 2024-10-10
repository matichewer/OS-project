#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/queue.h>

#define MAX_ORDERS 10

typedef enum {HAMBURGUESA, VEGANO, PAPAS} order_type;
typedef enum {STANDARD, VIP} customer_type;

typedef struct order_t {
    order_type type;
    customer_type customer;
    int id;
    TAILQ_ENTRY(order_t) entries;
} order_t;

void employee_worker(int read_fd, int write_fd, order_type role);
void customer_factory(int write_fd);
order_t* create_order(int id);
order_t* get_next_order();

TAILQ_HEAD(tailhead_vip, order_t) vip_queue;
TAILQ_HEAD(tailhead_std, order_t) std_queue;

int main(){
    int pipe_customers_to_employees[2];
    int pipe_employees_to_customers[2];

    // Crear pipes para la comunicacion entre clientes y empleados
    if (pipe(pipe_customers_to_employees) == -1) {
        perror("Error creating pipe for customers to employees");
        exit(1);
    }
    if (pipe(pipe_employees_to_customers) == -1) {
        perror("Error creating pipe for employees to customers");
        exit(1);
    }

    TAILQ_INIT(&vip_queue);
    TAILQ_INIT(&std_queue);
    
    // Crear procesos para los empleados (hamburguesas, vegano, papas fritas 1 y 2)
    pid_t employee_pids[4];
    order_type roles[4] = {HAMBURGUESA, VEGANO, PAPAS, PAPAS};

    for(int i = 0; i < 4; i++){
        employee_pids[i] = fork();
        if(employee_pids[i] == 0){
            // Proceso empleado
            close(pipe_customers_to_employees[1]);
            close(pipe_employees_to_customers[0]);
            employee_worker(pipe_customers_to_employees[0], pipe_employees_to_customers[1], roles[i]);
            exit(0);
        }
    }

    // Crear proceso para los clientes
    pid_t factory_pid;
    factory_pid = fork();
    if(factory_pid == 0){
        close(pipe_customers_to_employees[0]);
        close(pipe_employees_to_customers[1]);
        customer_factory(pipe_customers_to_employees[1]);
        exit(0);
    }

    waitpid(factory_pid, NULL, 0);

    for (int i = 0; i < 4; i++) {
        waitpid(employee_pids[i], NULL, 0);
    }

    close(pipe_customers_to_employees[0]);
    close(pipe_customers_to_employees[1]);
    close(pipe_employees_to_customers[0]);
    close(pipe_employees_to_customers[1]);

    return 0;
}

void employee_worker(int read_fd, int write_fd, order_type role) {
    order_t order;

    while (1) {
        order_t *next_order = get_next_order();
        if (next_order != NULL && next_order->type == role) {
            printf("Empleado %d preparando pedido %d de tipo %d (cliente %s)\n", getpid(), 
                    next_order->id, next_order->type, next_order->customer == VIP ? "VIP" : "STANDARD");
            sleep(2);
            write(write_fd, next_order, sizeof(order_t));
            free(next_order);
        }
    }
}

void customer_factory(int write_fd) {
    srand(time(NULL));
    int order_id = 1;
    
    while (1) {
        //int current_orders = TAILQ_COUNT(&vip_queue) + TAILQ_COUNT(&std_queue);
        if (1){
            sleep(rand() % 3 + 1);
            order_t* new_order = create_order(order_id);
            printf("Factory: Generando cliente con pedido %d (tipo %d, cliente %s)\n", new_order->id, 
                    new_order->type, new_order->customer == VIP ? "VIP" : "STANDARD");
            
            if (new_order->customer == VIP) {
                printf("inserta orden vip\n");
                TAILQ_INSERT_TAIL(&vip_queue, new_order, entries);
            } else {
                printf("inserta orden estandar\n");
                TAILQ_INSERT_TAIL(&std_queue, new_order, entries);
            }

            write(write_fd, new_order, sizeof(order_t));

            order_id++;
        }
    }
}

order_t* create_order(int id) {
    order_t* new_order = (order_t*)malloc(sizeof(order_t));
    new_order->id = id;
    new_order->type = rand() % 3;

    if (rand() % 100 < 80) {  // 80% de probabilidad para STANDARD
        new_order->customer = STANDARD;
    } else {  // 20% de probabilidad para VIP
        new_order->customer = VIP;
    } 
    
    return new_order;
}

order_t* get_next_order() {
    order_t* next_order;

    if (!TAILQ_EMPTY(&vip_queue)) {
        next_order = TAILQ_FIRST(&vip_queue);
        TAILQ_REMOVE(&vip_queue, next_order, entries);
    }

    else if (!TAILQ_EMPTY(&std_queue)) {
        next_order = TAILQ_FIRST(&std_queue);
        TAILQ_REMOVE(&std_queue, next_order, entries);
    }
    
    else {
        next_order = NULL;
    }

    return next_order;
}


