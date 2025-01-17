#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static volatile sig_atomic_t g_ack_received = 0;

void ack_handler(int sig) {
    (void)sig;
    g_ack_received = 1;
}

void wait_for_ack(void) {
    while (!g_ack_received) {
        usleep(50);  // Short sleep to prevent CPU hogging
    }
    g_ack_received = 0;
}

void send_signal(pid_t pid, int bit) {
    if (pid <= 0) {
        write(2, "Invalid PID\n", 12);
        exit(1);
    }
    
    g_ack_received = 0;
    
    if (kill(pid, bit ? SIGUSR2 : SIGUSR1) == -1) {
        write(2, "Signal sending failed\n", 21);
        exit(1);
    }
    
    wait_for_ack();
}

void send_message(pid_t pid, const char *message) {
    size_t len;
    size_t i;

    if (!message)
        return;
        
    len = 0;
    while (message[len])
        len++;

    i = 0;
    while (i <= len) {  // Include null terminator
        unsigned char c = message[i];
        for (int bit = 7; bit >= 0; bit--)
            send_signal(pid, (c >> bit) & 1);
        i++;
    }
}

int main(int ac, char **av) {
    struct sigaction sa;
    
    if (ac != 3) {
        write(2, "Usage: ./client <server_pid> <message>\n", 38);
        return (1);
    }
    
    // Setup acknowledgment handler
    sa.sa_handler = ack_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    
    if (sigaction(SIGUSR1, &sa, NULL) == -1) {
        write(2, "Signal setup failed\n", 19);
        return (1);
    }
    
    pid_t pid = atoi(av[1]);
    if (pid <= 0) {
        write(2, "Invalid PID\n", 12);
        return (1);
    }
    
    send_message(pid, av[2]);
    return (0);
}