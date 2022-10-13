#include <unistd.h>
#include <stdio.h>
#include <signal.h>
void hola(int signalNumb){
    printf("Recibi la senal %d", signalNumb);
    
}
int cond;
void terminarWhile(int signalNumb){
    printf("Terminando while\n");
    cond=0;
}
int main(){
    signal(12,terminarWhile);
    signal(2,hola);
    signal(19,hola);
    cond=1;
    while(cond == 1){
        printf("Trabajando\n");
        sleep(1);
    }
    printf("Aqui nunca llega\n");
    return 0;
}