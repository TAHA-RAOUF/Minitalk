// server.c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int sig) {
    static unsigned char character = 0;
    static int bit_count = 0;
    
    // Shift first, then set bit. This is more correct for bit ordering
    character = character << 1;
    if (sig == SIGUSR2)  // SIGUSR2 for 1, SIGUSR1 for 0
        character = character | 1;
    
    bit_count++;
    
    if (bit_count == 8) {
        write(1, &character, 1);  // Using write instead of printf for atomicity
        character = 0;
        bit_count = 0;
    }
}

int main(void) {
    struct sigaction sa;
    
    // Print PID with error checking
    if (write(1, "Server PID: ", 12) == -1)
        return (1);
    printf("%d\n", getpid());
    
    // Setup signal handling with sigaction for better reliability
    sa.sa_handler = signal_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    
    if (sigaction(SIGUSR1, &sa, NULL) == -1 ||
        sigaction(SIGUSR2, &sa, NULL) == -1) {
        write(2, "Signal setup failed\n", 19);
        return (1);
    }
    
    while (1)
        pause();  // More efficient than empty while loop
    return (0);
}