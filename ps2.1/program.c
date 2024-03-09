#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // if (argc != 4) {
    //     printf("Usage: %s source destination size\n", argv[0]);
    //     return 1;
    // }

    char *source = argv[1];
    char *destination = argv[2];
    int size = atoi(argv[3]);

    FILE *sourceFile = fopen(source, "rb");
    if (sourceFile == NULL) {
        printf("Failed to open source file\n");
        return 1;
    }

    FILE *destinationFile = fopen(destination, "wb");
    if (destinationFile == NULL) {
        printf("Failed to open destination file\n");
        fclose(sourceFile);
        return 1;
    }

    char *buffer = malloc(size);
    if (buffer == NULL) {
        printf("Failed to allocate memory\n");
        fclose(sourceFile);
        fclose(destinationFile);
        return 1;
    }

    size_t bytesRead;
    size_t bytesWritten;

    while ((bytesRead = fread(buffer, 1, size, sourceFile)) > 0) {
        bytesWritten = fwrite(buffer, 1, bytesRead, destinationFile);
        if (bytesWritten != bytesRead) {
            printf("Failed to write to destination file\n");
            break;
        }
    }

    free(buffer);
    fclose(sourceFile);
    fclose(destinationFile);
    //MArek
    return 0;
}
