#include <stdio.h>
#include <stdlib.h>
#include "client.h"

int main(){
    char input[10];
    int opt;

    do{
        system("clear");
        printf("===MENU===\n");
        printf("1. Ejecutar Comando en Equipo Remoto\n");
        printf("3. Salir\n");
        printf("Seleccione una Opcion\n");
        fgets(input, sizeof(input), stdin);  
        sscanf(input, "%d", &opt);

        switch(opt){
            case 1:
                exec_remote_cmd();
                printf("Presione Enter Para Continuar...\n");
                getchar();
                break;
            case 3:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion Invalida\n");
                printf("Presione Enter Para Continuar...\n");
                getchar();
                break;
        }
    } while (opt!=3);

    return 0;
}


