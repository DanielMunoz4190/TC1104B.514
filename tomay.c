#include <unistd.h>
#include <ctype.h> 
char minus(char may){
    if (may == 'A' || may == 'E' || may == 'I' || may == 'O' || may == 'U'){
        return '1';
    }
}
int main(){
    char c;
    char may;
    int n;
    do{
        n = read(STDIN_FILENO,&c,1);
        may = toupper(c);
        may = minus(may);
        write(STDOUT_FILENO,&may,1);
    }while(n != 0);
    return 0;
}