#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

char* expandEnvironmentVariables(const char* input) {
    char* result = malloc(MAX_BUFFER_SIZE);
    if (result == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    size_t resultIndex = 0;
    size_t inputIndex = 0;

    while (input[inputIndex] != '\0') {
        if (input[inputIndex] == '$' && input[inputIndex + 1] == '{') {
            // Found the start of an environment variable
            inputIndex += 2;
            size_t variableStart = inputIndex;

            while (input[inputIndex] != '\0' && input[inputIndex] != '}') {
                // Find the end of the environment variable
                inputIndex++;
            }

            if (input[inputIndex] == '}') {
                // Found the end of the environment variable
                size_t variableLength = inputIndex - variableStart;
                char variableName[variableLength + 1];
                strncpy(variableName, input + variableStart, variableLength);
                variableName[variableLength] = '\0';

                // Get the value of the environment variable
                char* variableValue = getenv(variableName);

                // Append the variable value to the result
                if (variableValue != NULL) {
                    size_t valueLength = strlen(variableValue);
                    if (resultIndex + valueLength >= MAX_BUFFER_SIZE - 1) {
                        fprintf(stderr, "Result buffer overflow\n");
                        exit(EXIT_FAILURE);
                    }
                    strncpy(result + resultIndex, variableValue, valueLength);
                    resultIndex += valueLength;
                }
            } else {
                // No closing '}' found, treat it as a regular character
                result[resultIndex++] = '$';
                result[resultIndex++] = '{';
                inputIndex = variableStart;
            }
        } else {
            // Regular character, copy it to the result
            result[resultIndex++] = input[inputIndex++];
        }
    }

    // Null-terminate the result string
    result[resultIndex] = '\0';

    return result;
}

int main() {
    const char* input = "Hello, ${USER}! Your home directory is ${HOME}.";
    char* result = expandEnvironmentVariables(input);

    printf("Original string: %s\n", input);
    printf("Expanded string: %s\n", result);

    free(result); // Don't forget to free the allocated memory

    return 0;
}
