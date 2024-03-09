#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//#define BUFFER_SIZE 4096

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Użycie: %s źródło cel rozmiar\n", argv[0]);
        return 1;
    }

    char *source_file = argv[1];
    char *destination_file = argv[2];
    int buffer_size = atoi(argv[3]);

    int source_fd = open(source_file, O_RDONLY);
    if (source_fd == -1) {
        perror("Błąd otwierania pliku źródłowego");
        return 1;
    }

    int destination_fd = open(destination_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destination_fd == -1) {
        perror("Błąd otwierania pliku docelowego");
        close(source_fd);
        return 1;
    }

    char *buffer = malloc(buffer_size);
    if (buffer == NULL) {
        perror("Błąd alokacji bufora");
        close(source_fd);
        close(destination_fd);
        return 1;
    }

    ssize_t bytes_read, bytes_written;
    while ((bytes_read = read(source_fd, buffer, buffer_size)) > 0) {
        bytes_written = write(destination_fd, buffer, bytes_read);
        if (bytes_written == -1) {
            perror("Błąd zapisu do pliku docelowego");
            free(buffer);
            close(source_fd);
            close(destination_fd);
            return 1;
        }
    }

    if (bytes_read == -1) {
        perror("Błąd odczytu z pliku źródłowego");
        free(buffer);
        close(source_fd);
        close(destination_fd);
        return 1;
    }

    free(buffer);
    close(source_fd);
    close(destination_fd);

    return 0;
}