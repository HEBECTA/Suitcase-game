#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "game-io.h"

#define SUITCASES_SIZE 26

long int make_offer(long int *suitCases, int picked_suitCase, int round);

bool valid_suitCase_selection(int index, long int *suitCases);

int main (int argc, const char* argv[])
{
    long int suitCases[SUITCASES_SIZE] = {
        0.01, 1, 5, 10, 25, 50, 75, 100, 200, 300,
     400, 500, 750, 1000, 5000, 10000, 25000, 50000, 75000, 100000,
      200000, 300000,400000, 500000, 750000, 1000000 };

    // get started here
    if ( argc == 2 )
    {
        if ( strcmp(argv[1], "-r") == 0)
        {
            printf(suffeling_suitcase_contents);

            srand(time(NULL));

            for (int i = 0; i < SUITCASES_SIZE; ++i ){

                int random_number = rand();

                random_number %= 26;

                double temp = suitCases[i];

                suitCases[i] = suitCases[random_number];

                suitCases[random_number] = temp;
            }
        }

        else
        {
            printf(argument_invalid, argv[1]);

            return EXIT_FAILURE;
        }
    }

    else if ( argc > 2){

        printf(arguments_too_many);

        return EXIT_FAILURE;
    }

    printf("[1][2][3][4][5][6][7][8][9][10][11][12][13][14][15][16][17][18][19][20][21][22][23][24][25][26]\n");

    printf(prompt_pick_prize);
    
    unsigned int number;

    do{

        askPlayerForNumber(&number);

    } while ( !valid_suitCase_selection(number-1, suitCases) );


    int picked_suitCase = number;
    suitCases[number-1] *= -1;

    printf(confirm_prize_suitcase, picked_suitCase);

    int eliminate = 6;
    int round = 1;

    int gameOn = true;

    while ( gameOn )
    {
        for (int i = 0; i < SUITCASES_SIZE; ++i){

           if (suitCases[i] < 0){

               continue;
           }

            printf("[%d]", i+1);
       }

        printf("\n");

        printf(intro_round, round, eliminate);

       for (int i = 0; i < eliminate; ++i){

           printf(prompt_pick_to_eliminate);

            do {

                askPlayerForNumber(&number);

                

            } while ( !valid_suitCase_selection(number-1, suitCases));

           printf(confirm_pick_to_eliminate, number, suitCases[number-1]);

           suitCases[number-1] = -2;
       }

       long int offer = make_offer(suitCases, picked_suitCase, round);

       printf(intro_bank_offer, offer);

       printf(prompt_bank_offer);

        yes_no_retry_t answer;

        bool error = false;

        do {

            if (error)
                printf(input_invalid);

            answer = askPlayerYesNo();

            error = true;

        } while ( answer == Retry );

       if ( answer == Yes ){

           gameOn = false;

           printf(confirm_bank_offer_gameover_early, offer);

           return EXIT_SUCCESS;
       }

        if (eliminate > 1 )
            --eliminate;

       ++round;

       if ( round > 9)
        gameOn = false;
    }

    int last_suitcase = -1;

    for (int i = 0; i < SUITCASES_SIZE; ++i){

        if ( suitCases[i] > 0 ){
            last_suitcase = i+1;
            break;
        }
    }

    printf(intro_switch_suitcase, picked_suitCase, last_suitcase);
    printf(prompt_switch_suitcase);

    yes_no_retry_t answer;

    do {

        answer = askPlayerYesNo();

    } while ( answer == Retry );

    if ( answer == Yes){

        printf(confirm_switch_suitcase, picked_suitCase, last_suitcase);

        picked_suitCase = last_suitcase;
    }

    else if ( answer == No)
        suitCases[picked_suitCase-1] *= -1;

    printf(game_over_full_game, picked_suitCase, suitCases[picked_suitCase-1]);

    return EXIT_SUCCESS;
}

long int make_offer(long int *suitCases, int picked_suitCase, int round){

    long int total_value = 0;
    int remaining = 0;

    for (int i = 0; i < SUITCASES_SIZE; ++i){

        if (suitCases[i] < -1 )
            continue;

        total_value += suitCases[i];
        ++remaining;
    }

    total_value += (suitCases[picked_suitCase-1] * -1);

    total_value /= remaining;
    total_value *= round;
    total_value /= 10;

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

    int rm = (int)total_value;

    total_value = (int)rm;

    return total_value;
}

bool valid_suitCase_selection(int index, long int *suitCases){

    if ( index < 0 || index > 26){

        printf(input_out_of_range);

        return 0;
    }

    else if (suitCases[index] < 0 ){

        printf(suitcase_not_availalbe);

        return 0;
    }

    return 1;
}