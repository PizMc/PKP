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

/*******************************************************************************
 *                              TYPEDEF
 ******************************************************************************/

/*******************************************************************************
 *                              DECLARATIONS
 ******************************************************************************/

extern BinS_result BinS_Search(const uint32_t lengthOfArray,
                               BinS_BINSCH givenArray[ lengthOfArray ],
                               BinS_BINSCH wantedElement,
                               BinS_result(*comparator)(BinS_BINSCH arg1, BinS_BINSCH arg2)
                              );  
extern bool BinS_Monotony( const uint32_t lengthOfArray, BinS_BINSCH givenArray[ lengthOfArray ] );


static BinS_result BinS_Init(void);
static BinS_result BinS_BinSearchStd(const uint32_t lengthOfArray,
                                        BinS_BINSCH givenArray[ lengthOfArray ],
                                        BinS_BINSCH wantedElement
                                       );
static BinS_result BinS_BinSearchUsr(const uint32_t lengthOfArray,
                                  BinS_BINSCH givenArray[ lengthOfArray ],
                                  BinS_BINSCH wantedElement,
                                  BinS_result(*comparator)(BinS_BINSCH arg1, BinS_BINSCH arg2)
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
 * @Limitations: Function does NOT sort arguments of givenArray they should be sorted before
 * @Note: Array can be sorted in either growing or decrising secuences
 * 
 **/ 
extern BinS_result BinS_BinSearch(const uint32_t lengthOfArray,
                                        BinS_BINSCH givenArray[ lengthOfArray ],
                                        BinS_BINSCH wantedElement,
                                        BinS_result(*comparator)(BinS_BINSCH arg1, BinS_BINSCH arg2)
                                      )
{
    BinS_result result = BinS_Init();

    /* if comparator is eq. NULL then user function is not given,
    so my own comparasion is made */
    if(NULL == comparator)
    {
        result = BinS_BinSearchStd(lengthOfArray, givenArray, wantedElement);
    }
    else
    {
        result = BinS_BinSearchUsr(lengthOfArray, givenArray, wantedElement, comparator);
    }

    return result;
}

/**
 * @Name: BinS_Monotony - BinSearch is the name of the file.
 * @Brief: Function evaluate if given array is sorted in growing, or decrising order
 * @Param1: length of array that is in Param2, the length of array have to be lower than 2^32
 * @Param2: array on witch we will do evaluation
 * @Return: return type bool in GROWING or DECRISING, with the natural meaning of eleemnts
 * 
 * @Limitations: Function does NOT sort arguments of givenArray they should be sorted before
 * @Note: Array can be sorted in either growing or decrising secuences
 * 
 **/ 
extern bool BinS_Monotony( const uint32_t lengthOfArray, BinS_BINSCH givenArray[ lengthOfArray ] );



/********************************************************************************
*                               STATIC DEFINITIONS
*********************************************************************************/

static BinS_result BinS_Init(void)
{
    BinS_result result_to_init = {  .index = 0U,
                                    /* casting is safe since 0 would be the same for all types */
                                    .foundValue = (BinS_BINSCH)0U,
                                    .found = BinS_NOT_FOUND
                                 };

    return result_to_init;
}


/////////////// TODO ///////////////////
/**
 *        Napisać deklaracje dla:
 *              >BinS_BinSearchUsr
 *              >BinS_BinSearchStd
 *        Popraw justowanie
 **/