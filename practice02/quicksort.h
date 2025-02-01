#ifndef QUICKSORT_H
#define QUICKSORT_H

#include "../practice01/structures/dl_list.h"

class QuickSortUtil {
private:
    static void quickSort(List&, int, int);
    friend void quickSort(List &list);
};


void QuickSortUtil::quickSort(List &list, int first, int last) {
    int mid = list[(first + last) / 2]->value;
    int tmpFirst = first, tmpLast = last;
    while (first < last) {
        while (list[first]->value < mid) first++;
        while (list[last]->value > mid) last--;
        if (first <= last) {
            list.swap(first, last);
            first++;
            last--;
        }
    }
    if (tmpFirst < last) quickSort(list, tmpFirst, last);
    if (first < tmpLast) quickSort(list, first, tmpLast);
}


void quickSort(List &list) {
    QuickSortUtil::quickSort(list, 0, int(list.getSize() - 1));
}

#endif //QUICKSORT_H