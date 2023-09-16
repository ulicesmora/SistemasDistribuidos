#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <puerto>\n", argv[0]);
        exit(1);
    }

    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(struct sockaddr_in);

    // Convertir el argumento del puerto a un entero
    int puerto = atoi(argv[1]);

    // Crear el socket del servidor
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Error al crear el socket del servidor");
        exit(1);
    }

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(puerto);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Enlazar el socket del servidor a la dirección y el puerto
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Error al enlazar el socket");
        exit(1);
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket, 10) == 0) {
        printf("Esperando conexiones...\n");
    } else {
        printf("Error al escuchar conexiones\n");
        exit(1);
    }

    // Aceptar la conexión entrante
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
    if (clientSocket < 0) {
        perror("Error al aceptar la conexión");
        exit(1);
    }
    printf("Conexión establecida con el cliente\n");

    char buffer[256];
    int num;
    while (1) {
        //limpiar el buffer
        memset(buffer, '\0', sizeof(buffer));

        // Recibir un número del cliente
        recv(clientSocket, buffer, sizeof(buffer), 0);

        // Convertir la cadena a un entero
        num = atoi(buffer);

        // Incrementar el número en uno
        num++;

        // Convertir el número incrementado de vuelta a una cadena
        snprintf(buffer, sizeof(buffer), "%d\n", num);

        printf("Enviado: %s\n", buffer);

        // Enviar el número incrementado de vuelta al cliente
        //send(clientSocket, &num, sizeof(int), 0);
        send(clientSocket, buffer, strlen(buffer), 0);


        if (num == 0) {
            printf("Cliente ha terminado la conexión\n");
            break;
        }
    }

    // Cerrar los sockets
    close(clientSocket);
    close(serverSocket);

    return 0;
}
