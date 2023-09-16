#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Uso: %s <dirección IP del servidor> <puerto>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int socketCliente;
    struct sockaddr_in servidorAddr;
    char mensaje[100];
    char respuesta[100];

    // Crear socket
    socketCliente = socket(AF_INET, SOCK_STREAM, 0);
    if (socketCliente == -1) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Configurar la dirección del servidor
    memset(&servidorAddr, 0, sizeof(servidorAddr));
    servidorAddr.sin_family = AF_INET;
    servidorAddr.sin_port = htons(atoi(argv[2]));
    servidorAddr.sin_addr.s_addr = inet_addr(argv[1]); // Dirección del servidor
    //"192.168.31.202"

    // Conectar al servidor
    if (connect(socketCliente, (struct sockaddr *)&servidorAddr, sizeof(servidorAddr)) == -1) {
        perror("Error al conectar con el servidor");
        exit(EXIT_FAILURE);
    }

    // Enviar mensaje al servidor
    strcpy(mensaje, "Hola\n");
    send(socketCliente, mensaje, strlen(mensaje), 0);

    // Recibir respuesta del servidor
    recv(socketCliente, respuesta, sizeof(respuesta), 0);
    printf("Servidor dice: %s\n", respuesta);

    // Cerrar la conexión
    close(socketCliente);

    return 0;
}
