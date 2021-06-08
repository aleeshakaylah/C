#ifndef __QUICK_H__
#define __QUICK_H__

#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>

long partition(long num_array[], long left, long right, Statistics *s);

//temp void
void quick_insertion(long num_array[], long left, long right, Statistics *s);

void quick_sort(Statistics *s);

#endif
