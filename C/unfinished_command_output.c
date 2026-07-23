#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *run_command(const char *cmd) {
    FILE *fp = popen(cmd, "r");

    size_t cap = 4096;
    size_t len = 0;
    char *output = malloc(cap);
    if (output == NULL) {
        pclose(fp);
        return NULL;
    }
    output[0] = '\0';

    char chunk[256];
    while (fgets(chunk, sizeof(chunk), fp) != NULL) {
        size_t chunk_len = strlen(chunk);

        if (len + chunk_len + 1 > cap) {
            cap *= 2;
            char *tmp = realloc(output, cap);
            if (tmp == NULL) {
                free(output);
                pclose(fp);
                return NULL;
            }
            output = tmp;
        }

        memcpy(output + len, chunk, chunk_len + 1);  
        len += chunk_len;
    }

    pclose(fp);
    return output;  
}

int main(void) {
    char *result = run_command("ls -la");
    if (result != NULL) {
        printf("Output:\n%s", result);
        free(result);
    }
    return 0;
}
