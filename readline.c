#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  // Added for realloc and exit
#include <string.h>

char **splitter(char *str)
{
    char *token, **tokens = NULL;
    int i = 0;
    
    token = strtok(str, " \t\n");
    while (token != NULL)
    {
        i++;
        tokens = realloc(tokens, (i + 1) * sizeof(char *));
        if (tokens == NULL)
        {
            perror("Memory allocation");
            exit(EXIT_FAILURE);
        } 
        tokens[i - 1] = token;
        token = strtok(NULL, " \t\n");
    }
    tokens[i] = NULL; // Null-terminate the tokens array

    for (i = 0; tokens[i]; i++)
        printf("%s\n", tokens[i]);  // Print each token on a new line

    return tokens;
}

int main(int ac, char **av)
{
    (void) ac;
    char *buffer = NULL, **tokens;
    size_t size_buffer = 0;
    int n_char = 0;

    write(1, "$ ", 2);
    
    n_char = getline(&buffer, &size_buffer, stdin);

    if (n_char == -1)
    {
        perror("getline");
        return 1;
    }
    buffer[n_char - 1] = '\0';  // Replace newline with null terminator

    tokens = splitter(buffer);

    free(buffer);  // Free the allocated buffer

    return 0;
}
