#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define SERVER_IP "192.168.1.245"
#define PORT 5555
#define BUFFER_SIZE 1024


//function to execute command in remote server
void exec_remote_cmd() {
    //soket function
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); exit(EXIT_FAILURE); }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    
    char comando[BUFFER_SIZE];
    printf("Ingrese el comando a ejecutar en el equipo remoto\n");
        // Leer desde stdin de forma segura
    if (fgets(comando, sizeof(comando), stdin) != NULL) {
        // Eliminar el salto de línea que deja fgets
        comando[strcspn(comando, "\n")] = '\0';

        // Enviar el comando al servidor
        send(sock, comando, strlen(comando), 0);
    } else {
        perror("Error al leer comando");
    }
    char respuesta [BUFFER_SIZE];
    int recibytes;
    
    while ((recibytes = recv(sock, respuesta, sizeof(respuesta) - 1, 0)) > 0) {
        respuesta[recibytes] = '\0';  // cortar el string
        printf("%s", respuesta);            // mostrar la salida en consola
    }

    close(sock);
}
