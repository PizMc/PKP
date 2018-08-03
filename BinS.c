/**
 *  @Author: Self
 *  
 *  @Brief: 
 * 
 *  @Usage: 
 * 
 *  @Limitations:   
 * 
 * @Date: 1.08.2018
 **/

/*******************************************************************************
 *                              INCLUDS
 ******************************************************************************/

/**
 *  @Brief: includs for types and declarations for binary search
 **/
#include "BinS.h"

/**
 *  @Brief: included for NULL declaration
 *  @Note: can be deleted when stdtypes powstanie
 **/
#include <stdlib.h>

/*******************************************************************************
 *                              DEFINE
 ******************************************************************************/

#define BinS_ARR_LEN(end, begin)   ((end) - (begin))

#define BinS_INIT(x) BinS_result x = {.index = 0U, \
                              /* casting is safe since 0 would be the same for all types */ \
                            .foundValue = (BinS_BINSCH)0U, \
                            .found = BinS_NOT_FOUND \
                           } \
                     

/*******************************************************************************
 *                              TYPEDEF
 ******************************************************************************/

/*******************************************************************************
 *                              DECLARATIONS
 ******************************************************************************/

extern BinS_result BinS_Search(const uint32_t lengthOfArray_cui32,
                               const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                               const BinS_BINSCH wantedElement,
                               int8_t(*comparator)(BinS_BINSCH arg1, BinS_BINSCH arg2)
                              );  
extern BinS_MONOTONYE BinS_Monotony(const uint32_t lengthOfArray_cui32,
                                    const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                                    int8_t(*comparator)(BinS_BINSCH arg1, BinS_BINSCH arg2)
                                   );


static BinS_result BinS_Init(void);
static BinS_result BinS_BinSearchStd(const uint32_t lengthOfArray_cui32,
                                     const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                                     const BinS_BINSCH wantedElement
                                    );
static BinS_result BinS_BinSearchUsr(const uint32_t lengthOfArray_cui32,
                                     const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                                     const BinS_BINSCH wantedElement,
                                     int8_t(*comparator)(BinS_BINSCH arg1, BinS_BINSCH arg2)
                                 );
static BinS_result BinSearchDecr(const uint32_t lengthOfArray_cui32,
                                 const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                                 const BinS_BINSCH wantedElement
                                );
static BinS_result BinSearchIncr(const uint32_t lengthOfArray_cui32,
                                 const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                                 const BinS_BINSCH wantedElement
                                );
/********************************************************************************
*                               EXTERN DEFINITIONS
*********************************************************************************/
/**
 * @Name: BinSearch_BinS - BinSearch is the name of the file.
 * @Brief: binary search req. that array is sorted inthis function it's unimpotant of order in which it is sorted
 *          !!! It is CRUCIAL to notice, that                     !!!
 *          !!! data type of array is definied as BinS_BINSCH typedef  !!!
 *          !!! under preprocesor flag__BinS_BINSCH_TYPE__             !!!
 *          which is default set to int8_tby this file
 * @Param1: length of array that is in Param2, the length of array have to be lower than 2^32
 * @Param2: array that we will do binary search on
 * @Param3: given value that we will search for
 * @Param4: pointer to function in which we could compare objects if returned type is traditional(int8_t,float,etc.)
 *          it is possible to set it to NULL, so standard compare would be make.
 *          Important to notice 1: comparator gets 2 arguments with type of BinS_BINSCH.
 *          Important to notice 2: comparator return type of binarySearch_result
 * @Return: return structure wiich consist all important information from given search
 * 
 * @Limitations: Function does NOT sort arguments of givenArray_a they should be sorted before
 * @Note: Array can be sorted in either growing or decrising secuences
 * 
 **/ 
extern BinS_result BinS_BinSearch(const uint32_t lengthOfArray_cui32,
                                  const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                                  const BinS_BINSCH wantedElement,
                                  int8_t(*comparator)(BinS_BINSCH arg1, BinS_BINSCH arg2)
                                 )
{
    BinS_result result_s = BinS_Init();

    /* if comparator is eq. NULL then user function is not given,
    so my own comparasion is made */
    if(NULL == comparator)
    {
        result_s = BinS_BinSearchStd(lengthOfArray_cui32, givenArray_a, wantedElement);
    }
    else
    {
        result_s = BinS_BinSearchUsr(lengthOfArray_cui32, givenArray_a, wantedElement, comparator);
    }

    return result_s;
}

/**
 * @Name: BinS_Monotony - BinSearch is the name of the file.
 * @Brief: Function evaluate if given array is sorted in growing, or decrising order
 * @Param1: length of array that is in Param2, the length of array have to be lower than 2^32
 * @Param2: array on witch we will do evaluation
 * @Return: return type bool in GROWING or DECRISING, with the natural meaning of eleemnts
 * 
 * @Limitations: Function does NOT sort arguments of givenArray_a they should be sorted before
 * @Note: Array can be sorted in either growing or decrising secuences
 * 
 **/ 
extern BinS_MONOTONYE BinS_Monotony(const uint32_t lengthOfArray_cui32,
                            const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                            int8_t(*comparator)(BinS_BINSCH arg1, BinS_BINSCH arg2)
                           )
{
    BinS_MONOTONYE monotony_e = BinS_DECRISING;
    uint32_t first_ui32 = 0U;
    uint32_t last_ui32 = lengthOfArray_cui32 - 1U; /* bc array numering starts from 0 */
    BinS_COMPARATORE cprResult_e = BinS_EQUAL;

    /* if there is special comparator, then use it */
    if (NULL == comparator)
    {
        /* casting is safe, since it is essentialy same type, and difference is only in naming */
        cprResult_e = (BinS_COMPARATORE)comparator(givenArray_a[ first_ui32 ], givenArray_a[ last_ui32 ]);

        if (BinS_SMALLER ==  cprResult_e)
        {
            monotony_e = BinS_DECRISING;
        }
        else if (BinS_EQUAL == cprResult_e)
        {
            monotony_e = BinS_CONST;
        }
        else    /* true: BinS_BIGGER == cprResult_e  */
        {
            monotony_e = BinS_INCRESING;
        }
    }
    /* there's nospecial cpr use standard comaparation */
    else
    {
        if (givenArray_a[ first_ui32 ] > givenArray_a[ last_ui32 ])
        {
            monotony_e = BinS_DECRISING;
        }
        else if (givenArray_a[ first_ui32 ] < givenArray_a[ last_ui32 ])
        {
            monotony_e = BinS_INCRESING;
        }
        else    /* true: arr[0] == arr[last] */
        {
            monotony_e = BinS_CONST;
        }
    }/* if (NULL == comparator) */

    return monotony_e;
}



/********************************************************************************
*                               STATIC DEFINITIONS
*********************************************************************************/

static BinS_result BinS_Init(void)
{
    BinS_result result_s = {.index = 0U,
                              /* casting is safe since 0 would be the same for all types */
                            .foundValue = (BinS_BINSCH)0U,
                            .found = BinS_NOT_FOUND
                           };

    return result_s;
}

static BinS_result BinSearchIncr(const uint32_t lengthOfArray_cui32,
                                 const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                                 const BinS_BINSCH wantedElement
                                );


/////////////// TODO ///////////////////
/**
 *        Napisać deklaracje dla:
 *              >BinS_BinSearchUsr
 *              >BinS_BinSearchStd
 *        Popraw justowanie
 **/

static BinS_result BinS_BinSearchStd(const uint32_t lengthOfArray_cui32,
                                     const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                                     const BinS_BINSCH wantedElement
                                    )
{
    BinS_result result_s = {
                            .index = 0U,
                            .foundValue = (BinS_BINSCH)0,
                            .found = FALSE
                         };
    /* unused variable
    uint32_t index_ui32 = lengthOfArray_cui32 / (uint32_t)2U;*/ /* casting for proving intentional intiger divide */

    BinS_MONOTONYE monotony = BinS_Monotony(lengthOfArray_cui32, givenArray_a, NULL);

    if (BinS_DECRISING == monotony)
    {
        result_s = BinSearchDecr(lengthOfArray_cui32, givenArray_a, wantedElement);

    }/*true: BinS_DECRISING == monotony */
    else if (BinS_INCRESING == monotony)
    {
        result_s = BinSearchIncr(lengthOfArray_cui32, givenArray_a, wantedElement);

    }/* true: BinS_INCRESING == monotony */
    else
    /* true: BinS_CONST == monotony */
    {/* then all elements in givenArray_a are eq. */

        if(givenArray_a[ 0 ] == wantedElement)
        {
            result_s.index = 0U,
            result_s.foundValue = givenArray_a[ 0 ],
            result_s.found = TRUE;
        }
        else
        {
            /* this could be ommit, bc it was allraedy initialized */
            result_s.found = FALSE;  /* for constistency, compilator probbaly will get rid of that */                 
        }

    }/* true: BinS_CONST == monotony */

    return result_s;
}


static BinS_result BinSearchDecr(const uint32_t lengthOfArray_cui32,
                                     const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                                     const BinS_BINSCH wantedElement
                                    )
{
    //BinS_result result_s = BinS_Init();
    BinS_INIT(result_s);

    uint32_t index_ui32 = lengthOfArray_cui32 / (uint32_t)2U;    /* cast to make it clear */
    uint32_t head_ui32 = lengthOfArray_cui32 - 1U; /* -1 bc numering array starts from 0 not from 1 */
    uint32_t tail_ui32 = 0U;
    uint32_t calcMem_ui32 = 0U;

    while (FALSE == result_s.found 
           || head_ui32 == tail_ui32 )
    {
        if (givenArray_a[ index_ui32 ] == wantedElement)
        {
            result_s.found = TRUE;
            result_s.foundValue = givenArray_a[ index_ui32 ];
            result_s.index = index_ui32;
        }
        else
        {
            if (wantedElement > givenArray_a[ index_ui32 ])
            {
                head_ui32 = index_ui32 -1U;     /* bc we allraedy know that under index_ui32 is not our element, but lowe */
                calcMem_ui32 = BinS_ARR_LEN(head_ui32, tail_ui32) / (uint32_t)2U;

                index_ui32 = head_ui32 - calcMem_ui32;
            }
            else
            {
                tail_ui32 = index_ui32 + 1U;    /* bc we allraedy know that under index_ui32 is not our element, but higher */
                calcMem_ui32 = BinS_ARR_LEN(head_ui32, tail_ui32) / (uint32_t)2U;

                index_ui32 = tail_ui32 + calcMem_ui32;
            }
        }
    }/* while (FALSE == result_s.found) */

    return result_s;
}


static BinS_result BinSearchIncr(const uint32_t lengthOfArray_cui32,
                                     const BinS_BINSCH givenArray_a[ lengthOfArray_cui32 ],
                                     const BinS_BINSCH wantedElement
                                    )
{
    //BinS_result result_s = BinS_Init();
    BinS_INIT(result_s);

    uint32_t index_ui32 = lengthOfArray_cui32 / (uint32_t)2U;    /* cast to make it clear */
    uint32_t head_ui32 = lengthOfArray_cui32 - 1U; /* -1 bc numering array starts from 0 not from 1 */
    uint32_t tail_ui32 = 0U;
    uint32_t calcMem_ui32 = 0U;

    while (FALSE == result_s.found 
           || head_ui32 == tail_ui32 )
    {
        if (givenArray_a[ index_ui32 ] == wantedElement)
        {
            result_s.found = TRUE;
            result_s.foundValue = givenArray_a[ index_ui32 ];
            result_s.index = index_ui32;
        }
        else
        {
            if (wantedElement < givenArray_a[ index_ui32 ])
            {
                head_ui32 = index_ui32 -1U;     /* bc we allraedy know that under index_ui32 is not our element, but lowe */
                calcMem_ui32 = BinS_ARR_LEN(head_ui32, tail_ui32) / (uint32_t)2U;

                index_ui32 = head_ui32 - calcMem_ui32;
            }
            else
            {
                tail_ui32 = index_ui32 + 1U;    /* bc we allraedy know that under index_ui32 is not our element, but higher */
                calcMem_ui32 = BinS_ARR_LEN(head_ui32, tail_ui32) / (uint32_t)2U;

                index_ui32 = tail_ui32 + calcMem_ui32;
            }
        }
    }/* while (FALSE == result_s.found) */

    return result_s;
}


/*

wanted = 6


        i                  head = 9     tail = 0
0 1 2 3 4 5 6 7 8 9        0 2 3 4 5 6 7 8 9 

              i            head = 9     tail = 5
0 1 2 3 4 5 6 7 8 9        5 6 7 8 9

                           head = 7     tail = 5
0 1 2 3 4 5 6 7 8 9         

      i                    head = 4     tail = 4
0 1 2 3 4 5 6 7 8 9        4




*/