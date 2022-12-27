#include <stdio.h>
#include <stdlib.h>

#define MAX_BYTES 1026

int seirosian(int is_true);

int main(void) {

    char my_str[MAX_BYTES];

    fgets(my_str, MAX_BYTES, stdin);

    printf("Your str: %s\n", my_str);

    int is_seirosian = seirosian(1);



    return 0;
}

int seirosian(int is_true) {
    if (is_true) {
        printf("Seiros!!");
        return 4;
    } else {
        printf("Not Seiros");
        return 5;
    }
}