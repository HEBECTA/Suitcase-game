#include <stdio.h>

int main(){

    
    long int total_value = 15036.1465;
    long int tmp = total_value;
    int digits = 0;

    while ( tmp > 0 ){

        tmp /= 10;

        digits += 1;
    }

    if ( digits > 2 ){

        int a = digits - 3;

        long int p = 1;

        for (int i = 0; i < a; ++i){

            p *= 10;
        }

        long int third_signi_digit = total_value / p;

        third_signi_digit %= 10;

        if ( third_signi_digit > 0 ){

            total_value /= p * 10;

            ++total_value;

            total_value *= p * 10;
        }

        else{

            total_value /= p;

            total_value *= p;
        }
    }

    long int rm = total_value;

    ++rm;

    long int rem = rm - total_value;

    total_value -= rem;

    printf("%ld.%02ld", total_value);

    return 0;
}