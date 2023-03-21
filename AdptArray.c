#include "AdptArray.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct AdptArray_
{
    PElement * PElemArr;
    DEL_FUNC delF;
    COPY_FUNC copyF;
    PRINT_FUNC printF;
    int arrSize;
} AdptArray, *PAdptArray;


PAdptArray CreateAdptArray(COPY_FUNC copy, DEL_FUNC del, PRINT_FUNC print)
{   
    if (!print || !del || !copy) return NULL;
    PAdptArray pAA =(PAdptArray)malloc(sizeof(AdptArray));
    if (!pAA) return NULL;
    pAA->arrSize = 0;
    pAA->PElemArr = NULL;
    pAA->delF = del;
    pAA->copyF = copy;
    pAA->printF = print;
    return pAA;
}


void DeleteAdptArray(PAdptArray pAA)
{
    if(!pAA) return;
    if (pAA->arrSize > 0)
    {
        pAA->delF((pAA->PElemArr));
    }
    free(pAA);
}


// Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
// {
//     int changed = 0;
//     PElement *newpElemArr;
//     if (pArr == NULL || idx < 0)
//         return FAIL;
//     if (idx >= pArr->arrSize)
//     {
//         if ((newpElemArr = (PElement *)calloc((idx + 1), sizeof(PElement))) ==NULL)
//             return FAIL;
// 		for (int i = 0; i < pArr->arrSize; i++)
//         {
//             newpElemArr[i] = (pArr->PElemArr)[i];
//         }
//         newpElemArr[idx] = pArr->copyF(pNewElem);
//         free(pArr->PElemArr);
// 		pArr->PElemArr = newpElemArr;
//         changed = 1;
//     }
//     else{
//         pArr->delF((pArr->PElemArr)[idx]);
//         (pArr->PElemArr)[idx] = pArr->copyF(pNewElem);
//     }
//     if( changed == 1)
//         pArr->arrSize = idx + 1;
//     return SUCCESS;
// }

Result SetAdptArrayAt(PAdptArray pAA, int i, PElement pNew)
{
    PElement* newElem;
    if(!pAA || !pNew) return FAIL;

    if(i >= pAA->arrSize)
    {   
        int x;
        if((newElem = (PElement*)calloc((i+1), sizeof(PElement))) == NULL) return FAIL;
        for(x = 0; x < pAA->arrSize; x++)
        {
            newElem[x] = (pAA->PElemArr)[x];
        }
        memcpy(newElem, pAA->PElemArr, (pAA->arrSize)*sizeof(PElement));
        free(pAA->PElemArr);
        pAA->PElemArr = newElem;
    }
    else
    {
        pAA->delF((pAA->PElemArr)[i]);
    }
    (pAA->PElemArr)[i] = pAA->copyF(pNew);
    if(i >= pAA->arrSize) pAA->arrSize = i+1;
    return SUCCESS;
}

PElement GetAdptArrayAt(PAdptArray pAA, int i){
    if(pAA == NULL) return NULL;
    if( i < 0 || i > (pAA->arrSize)) return NULL;
    return ((pAA->PElemArr)[i]);
}


int GetAdptArraySize(PAdptArray pAA) 
{
    if(!pAA) return 0;
    return pAA->arrSize;
}

void PrintDB(PAdptArray pAA)
{
    if(!pAA) return;
    if(pAA->arrSize == 0) 
    {
        printf("size 0\n"); 
        return;
    }
    else{
        int i;
        for(i=0; i< pAA->arrSize; i++)
        {
            if((pAA->PElemArr[i]))
            {
                pAA->printF(pAA->PElemArr[i]);
            }
        }
    }
}