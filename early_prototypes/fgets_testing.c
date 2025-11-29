#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define IGNORE 32

int main() {
    char input[40];
    char lower_case[20] = {0};
    char upper_case[20] = {0};
    char tokens[5][20];
    int token_count = 0;

    char current[20];
    int cur_index = 0;

    int index = 0;

    int num, size1, item1;

    int size2, item2;

    printf("Enter what you want: \n");
    fgets(input, sizeof(input), stdin);

    // This for loop makes it the array all into lowercase.
    for (index = 0; input[index] != '\0'; index++) {
        lower_case[index] = tolower(input[index]);
    }

    printf("Lowercase verison of the string:\n%s", lower_case);

    // This for loop makes it the array all into uppercase.
    for (index = 0; input[index] != '\0'; index++) {
        upper_case[index] = toupper(input[index]);
    }

    printf("Uppercase version of the string:\n%s", upper_case);

    for (int index = 0; input[index] != '\0'; index++) {
        if (input[index] == IGNORE) {
            ;
        }
        if (input[index] != IGNORE || input[index + 1] == IGNORE) {
            lower_case[index] = input[index];
            upper_case[index] = input[index];

            if (upper_case[index] > 64 && upper_case[index] < 91) {
                size2 += upper_case[index];
                item2 = size2 / 2;
                // printf("\nThis one is special:\n%c", upper_case[index]);
            }

            if (lower_case[index] > 96 && lower_case[index] < 123) {
                size1 += lower_case[index];
                item1 = size1 / 2;
                // printf("\nThis one is special:\n%c", lower_case[index]);
            }

            if (input[index] > 47 && input[index] < 58) {
                num = input[index];
            }

            // printf("%c", lower_case[index]);
        }

        // printf("%c", input[i]);
    }

    printf("The number is:\n%d", num);
    printf("\nLowercase numbers:\n%d\n%d", size1, item1);
    printf("\nUppercase numbers:\n%d\n%d", size2, item2);

    // printf("%c", input[0]);
    // printf("You entered:\n%s", input);

    return 0;
}
