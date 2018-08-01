/**
 *  @Author: Self
 *  
 *  @Brief: File contains deklarations of functions, that are used
 *          in BinS.c file
 *          Contains declaration of binSch type
 *          that type is default set by this file to int8_t
 *          under flag __BINSCH_TYPE__
 *          declared functions and array works on that type (check declar.)
 * 
 *  @Usage: If usege of type diff. than int8_t is required, then 
 *          type of elements in array, should be defined as binSch
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

#ifdef __BINSEARCH_INT8__
#define __BINSEARCH_INT8__

/*******************************************************************************
 *                              INCLUDS
 ******************************************************************************/

/**
 *  @Brief: includs for different int types
 *  @Note: it could be done probably by one of them,
 *         given 2 for consistency with different compilers
 *  @TODO: check if one of (stdint or inttypes) is enough
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
 *  @Type: binSch - type that bin search will be done in
 * 
 **/

/*******************************************************************************
 *                              DEFINE
 ******************************************************************************/

#ifndef __BINSCH_TYPE__
    #define int8_t binSch;
#endif  __BINSCH_TYPE__

#ifndef __DECRISING__
    #define DECRISING 0U        /* by the exception that 0 means false */
#endif


#ifndef __GROWING__
    #define GROWING !DECRISING  /* logical negation of false is true which is DECRISING wanted value*/
#endif

/*******************************************************************************
 *                              TYPEDEF
 ******************************************************************************/

typedef struct {
    uint32_t    index;
    binSch      foundValue;
    bool        found;
} binarySearch_result;


/*******************************************************************************
 *                              DECLARATIONS
 ******************************************************************************/

/**
 * @Name: BinSearch_BinS - BinSearch is the name of the file.
 * @Brief: binary search req. that array is sorted inthis function it's unimpotant of order in which it is sorted
 *          !!! It is CRUCIAL to notice, that                     !!!
 *          !!! data type of array is definied as binSch typedef  !!!
 *          !!! under preprocesor flag__BINSCH_TYPE__             !!!
 *          which is default set to int8_tby this file
 * @Param1: length of array that is in Param2, the length of array have to be lower than 2^32
 * @Param2: array that we will do binary search on
 * @Param3: given value that we will search for
 * @Param4: pointer to function in which we could compare objects if returned type is traditional(int8_t,float,etc.)
 *          it is possible to set it to NULL, so standard compare would be make.
 *          Important to notice 1: comparator gets 2 arguments with type of binSch.
 *          Important to notice 2: comparator return type of binarySearch_result
 * @Return: return structure wiich consist all important information from given search
 * 
 * @Limitations: Function does NOT sort arguments of givenArray they should be sorted before
 * @Note: Array can be sorted in either growing or decrising secuences
 * 
 **/ 
extern binarySearch_result BinSearch_BinS(  const uint32_t lengthOfArray,
                                            binSch givenArray[ lengthOfArray ],
                                            binSch wantedElement,
                                            (void*)(*comparator)(binSch arg1, binSch arg2)
                                         );

/**
 * @Name: BinarySearchInt8_Monotony - BinSearch is the name of the file.
 * @Brief: Function evaluate if given array is sorted in growing, or decrising order
 * @Param1: length of array that is in Param2, the length of array have to be lower than 2^32
 * @Param2: array on witch we will do evaluation
 * @Return: return type bool in GROWING or DECRISING, with the natural meaning of eleemnts
 * 
 * @Limitations: Function does NOT sort arguments of givenArray they should be sorted before
 * @Note: Array can be sorted in either growing or decrising secuences
 * 
 **/ 
extern bool BinarySearchInt8_Monotony( const uint32_t lengthOfArray, binSch givenArray[ lengthOfArray ] );

#endif /* __BINSEARCH_INT8__ */