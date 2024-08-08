#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int y2015d1p1(FILE *input_file, int *result) {
    int sum = 0;
    char buffer[BUFSIZ];
    errno = 0;
    while (buffer == fgets(buffer, BUFSIZ, input_file)) {
        for (size_t i = 0; i<BUFSIZ; ++i) {
            switch (buffer[i]) {
                case '\0':
                    goto BREAK_FOR;
                case '(':
                    sum += 1;
                    break;
                case ')':
                    sum -= 1;
                    break;
                default:
                    fprintf(stderr, "Error: unknown character '%hhx'\n", (unsigned char) buffer[i]);
                    return EXIT_FAILURE;
            }
        }
        BREAK_FOR:;
    }
    if (ferror(input_file)) {
        perror(NULL);
        return EXIT_FAILURE;
    }

    *result = sum;
    return EXIT_SUCCESS;
}

int direct_mode(int argc, char **argv) {
    int return_value = EXIT_FAILURE;
    
    if (argc != 2) {
        fprintf(stderr, "Error: 1 argument expected, %d received\n", argc-1);
        return return_value;
    }

    FILE *input_file;
    errno = 0;
    if (!(input_file = fopen(argv[1], "r"))) {
        perror(NULL);
        return return_value;
    }

    int sum = 0;
    if (!y2015d1p1(input_file, &sum)) {
        printf("Result: %d\n", sum);
        return_value = EXIT_SUCCESS;
    }
    
    fclose(input_file);
    return return_value;
}

int interactive_mode() {
    int return_value = EXIT_FAILURE;
    printf("Enter input file path: ");
    fflush(stdout);
    char buffer[BUFSIZ];
    errno = 0;
    if (buffer != fgets(buffer, BUFSIZ, stdin)) return EXIT_FAILURE;
    buffer[strcspn(buffer,"\r\n")] = '\0';
    FILE *input_file;
    errno = 0;
    if (!(input_file = fopen(buffer, "r"))) {
        perror(NULL);
        return EXIT_FAILURE;
    }

    int sum = 0;
    if (!y2015d1p1(input_file, &sum)) {
        printf("Result: %d\n", sum);
        return_value = EXIT_SUCCESS;
    }
    
    fclose(input_file);
    return return_value;
}

int main(int argc, char **argv) {
    if (argc == 1) {
        return interactive_mode();
    }
    else {
        return direct_mode(argc, argv);
    }
}
