#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork hiba");
        return 1;
    }
    else if (pid == 0) {
        // --- GYEREK FOLYAMAT ---
        printf("[GYEREK] Én vagyok a gyerek (PID: %d). 2 másodperc múlva kilépek.\n", getpid());
        sleep(2);
        printf("[GYEREK] Most lépek ki (és válok zombivá, mert apu nem figyel rám)...\n");
        exit(0); // A gyerek itt befejezi, de a státusza megmarad
    }
    else {
        // --- SZÜLŐ FOLYAMAT (JAVÍTOTT) ---
        printf("[SZÜLŐ] Én vagyok a szülő. Várok a gyerekre...\n");
        
        // Ez a sor a kulcs! Megvárja, amíg a gyerek kilép, és törli a bejegyzését.
        wait(NULL); 
        
        printf("[SZÜLŐ] A gyerek kilépett, a wait() rendet rakott utána.\n");
        printf("[SZÜLŐ] Még alszom 5 másodpercet, nézd meg most a ps-t (nem lesz zombi)!\n");
        sleep(5);
    }
    return 0;
}
