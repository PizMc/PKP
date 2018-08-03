
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "BinS.h"

int8_t comparer(BinS_BINSCH arg1, BinS_BINSCH arg2);


int main(void)
{
    const uint32_t length = 10U;
    int8_t arr[ length ];
    uint32_t i = 0;
    uint32_t j = 0;
    for(i = 0; i < length; i++)
    {
        arr[ i ] = i;
        printf("%d ",i);
    }
    arr[ i ] = i; printf("%d ",i);
    puts("");

    BinS_MONOTONYE monotony = BinS_Monotony(length, arr, &comparer);

    printf("monotony: ");

    switch( monotony )
    {
        case BinS_DECRISING: printf("decrising");
                             break;
        case BinS_INCRESING: printf("incrising");
                             break;
        case BinS_CONST: printf("constans");
                         break;
        default:
            printf("Samething gone terribly wrong");

    }

    puts("");
 int8_t wanted= 0;
    for(i = 0; i < length; i++){
    wanted = (int8_t)i;
    BinS_result result = BinS_BinSearch(length, arr, wanted, &comparer);

    printf("\nwanted: %d\n",wanted);
    printf("found: ");
    result.found ? printf("TRUE") : printf("FALSE");
    puts("");

    printf("foundValue: %d\n", result.foundValue);

    printf("index: %d\n",result.index);
    }

    return EXIT_SUCCESS;
}


int8_t comparer(BinS_BINSCH arg1, BinS_BINSCH arg2)
{
    BinS_COMPARATORE toReturn_e;

    if (arg2 > arg1)
    {
        toReturn_e = BinS_BIGGER;
    }
    else if (arg2 < arg1)
    {
        toReturn_e = BinS_SMALLER;
    }
    else
    {
        toReturn_e = BinS_CONST;
    }

    return (int8_t)toReturn_e;
}