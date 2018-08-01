/**
 *  @Author: Self
 *  
 *  @Brief: File contains deklarations of functions, that are used
 *          in BinS.c file
 *          Contains declaration of BINSCH type
 *          that type is default set by this file to int8_t
 *          under flag __BINSCH_TYPE__
 *          declared functions and array works on that type (check declar.)
 * 
 *  @Usage: If usege of type diff. than int8_t is required, then 
 *          type of elements in array, should be defined as BINSCH
 *          with preprocesor flag __BINSCH_TYPE__
 *          Function BinSearch_BinS should be used to binary search array
 *          Function BinarySearchInt8_Monotony can be used to test monotony
 *          of array
 * 
 *  @Limitations:   THERE IS BRAVE ASUMPTION THAT LENGTH OF ARRAY
 *                  WILL FIT INTO 32 UNSIG. BYTES
 *                  AND
 *                  THAT ARRAY IS SORTED
 * 
 * @Date: 31.07.2018
 **/

#ifndef __BINSEARCH_INT8__
#define __BINSEARCH_INT8__

/*******************************************************************************
 *                              INCLUDS
 ******************************************************************************/

/**
 *  @Brief: includs for different int types
 *  @Note: it could be done probably by one of them,
 *         given 2 for consistency with different compilers
 *  @TODO: check if one of (stdint or inttypes) is enoug
 **/
#include <stdint.h>
#include <inttypes.h>

/** 
 * @Breief: for floating points types
 **/
#include <float.h>

/**
 * @Brief: for boolean typ consistency
 **/
#include <stdbool.h>

/**
 *  @Brief: declaration of used in file type
 * 
 *  @Type: BINSCH - type that bin search will be done in
 * 
 **/

/*******************************************************************************
 *                              DEFINE
 ******************************************************************************/

#ifndef __BinS_DECRISING__
#define __BinS_DECRISING__
    #define BinS_DECRISING (0U)        /* by the exception that 0 means false */
#endif

#ifndef __BinS_GROWING__
#define __BinS_GROWING__
    #define BinS_GROWING (!BinS_DECRISING)  /* logical negation of false is true which is DECRISING wanted value*/
#endif

#ifndef __BinS_NOT_FOUND__
#define __BinS_NOT_FOUND__
    #define BinS_NOT_FOUND (0U)  /* logical negation of false is true which is DECRISING wanted value*/
#endif

#ifndef __BinS_FOUND__
#define __BinS_FOUND__
    #define BinS_FOUND (!NOT_FOUND)  /* logical negation of false is true which is DECRISING wanted value*/
#endif

/*******************************************************************************
 *                              TYPEDEF
 ******************************************************************************/

/**
 *  @Brief: declaring new type for usage in binary search as default type - int8_t
 *  @Usage: If different type is wanted to be used in binary search, then it have to be
 *          ! typedef with name BinS_BINSCH
 *          ! and compilation flag__BinS_BINSCH_TYPE__
 *          ! declared before including BinS.h
 **/
#ifndef __BinS_BINSCH_TYPE__
#define __BinS_BINSCH_TYPE__
    typedef int8_t BinS_BINSCH;
#endif /*__BinS_BINSCH_TYPE__*/

/**
 *  @Brief: structure declared as an output from binarySearch function
 *          gives all needed information about given search
 *  @param1: index - gives place in tab that first occour of element to search was found
 *  @param2: foundValue - value that was given to search for, placed here for consistency of 
 *           all needed informations. If value was not found it's set to 0
 *  @param3: found - says if value was found (FOUND) or not (NOT_FOUND)
 **/
typedef struct {
    uint32_t    index;
    BinS_BINSCH foundValue;
    bool        found;
} BinS_result;


/*******************************************************************************
 *                              DECLARATIONS
 ******************************************************************************/

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
extern BinS_result BinS_SearchFunction(  const uint32_t lengthOfArray,
                                            BinS_BINSCH givenArray[ lengthOfArray ],
                                            BinS_BINSCH wantedElement,
                                            BinS_result(*comparator)(BinS_BINSCH arg1, BinS_BINSCH arg2)
                                         );

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

#endif /* __BINSEARCH_INT8__ */