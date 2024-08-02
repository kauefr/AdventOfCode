#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(int argc, char **argv) {
    int return_value = EXIT_SUCCESS;
    if (argc != 2) {
        fprintf(stderr, "Error: 1 argument expected, %d received\n", argc-1);
        return_value = EXIT_FAILURE;
        goto RETURN;

    }

    FILE *fp;
    if (!(fp = fopen(argv[1], "r"))) {
        perror(NULL);
        return_value = EXIT_FAILURE;
        goto RETURN;
    }
    //fp is open


    int sum = 0;
    char buffer[BUFSIZ];
    while (buffer == fgets(buffer, BUFSIZ, fp)) {
        for (size_t i = 0; i<BUFSIZ; ++i) {
            switch (buffer[i]) {
                case '\0':
                    goto END_FOR;
                case '(':
                    sum += 1;
                    break;
                case ')':
                    sum -= 1;
                    break;
                default:
                    fprintf(stderr, "Error: unknown character '%hhx'\n", (unsigned char) buffer[i]);
                    return_value = EXIT_FAILURE;
                    goto CLOSE;
            }
        } END_FOR:
    }
    //fgets returned 0
    if (ferror(fp)) {
        perror(NULL);
        return_value = EXIT_FAILURE;
        goto CLOSE;
    }



    printf("Result: %d\n", sum);
    CLOSE:
    fclose(fp);
    RETURN:
    return return_value;
}
