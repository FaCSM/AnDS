#ifndef TIMSORT_H
#define TIMSORT_H

#include "../practice01/structures/dl_list.h"
#include "stack/stack.h"

class TimSortUtils {
private:
    static void insertionSort(List&);
    static int getMinRun(int);
    static Stack getRuns(List&);
    static int binarySearch(List&, int);
    static List merge(List&, List&);

    friend void timSort(List &list);
};

void TimSortUtils::insertionSort(List &list) {
    for (int i = 1; i < list.getSize(); ++i)
        for (int j = i; j > 0 && list[j - 1]->value > list[j]->value; --j)
            list.swap(j, j-1);
}

int TimSortUtils::getMinRun(int n) {
    int mask = 0;
    while (n >= 64) {
        mask |= n & 1;
        n >>= 1;
    }
    return n + mask;
}

Stack TimSortUtils::getRuns(List &list) {
    int size = (int) list.getSize();
    int minRun = getMinRun(size);
    Stack sorted;

    for (int i = 0; i < size; ++i) {
        List run;
        run.append(list[i]->value);

        if (list[i]->value <= list[i+1]->value) {
            while ((i < size - 1) && (list[i]->value <= list[i+1]->value))
                run.append(list[++i]->value);
        } else {
            while ((i < size - 1) && (list[i]->value > list[i+1]->value))
                run.append(list[++i]->value);
            run.reverse();
        }

        while ((i < size - 1) && (run.getSize() < minRun))
            run.append(list[++i]->value);

        insertionSort(run);
        sorted.push(run);
    }

    return sorted;
}

int TimSortUtils::binarySearch(List& list, int key) {
    int left = 0;
    int right = (int) list.getSize() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        struct Node *midNode = list[mid];
        if (midNode->value == key) return mid;
        else if (midNode->value < key) left = mid + 1;
        else right = mid - 1;
    }

    return list[right]->value == key ? right : -1;
}


List TimSortUtils::merge(List &a, List &b) {
    const unsigned short N = 7;
    unsigned short consecutive = 0;
    bool isFromA = true;

    List result;
    struct Node *aNode = a[0];
    struct Node *bNode = b[0];

    while (aNode && bNode) {
        if (consecutive == N) {
            consecutive = 0;
            if (isFromA) {
                int insertWhile = binarySearch(a, bNode->value);
                if (insertWhile < 0) continue;

                for (; aNode && aNode->value <= a[insertWhile]->value; aNode = aNode->next)
                    result.append(aNode->value);
                result.append(bNode->value);
                bNode = bNode->next;
            } else {
                int insertWhile = binarySearch(b, aNode->value);
                if (insertWhile < 0) continue;

                for (; bNode && bNode->value <= b[insertWhile]->value; bNode = bNode->next)
                    result.append(bNode->value);
                result.append(aNode->value);
                aNode = aNode->next;
            }
        } else {
            if (aNode->value <= bNode->value) {
                if (isFromA) consecutive++;
                else {
                    consecutive = 1;
                    isFromA = true;
                }
                result.append(aNode->value);
                aNode = aNode->next;
            } else {
                if (!isFromA) consecutive++;
                else {
                    consecutive = 1;
                    isFromA = false;
                }
                result.append(bNode->value);
                bNode = bNode->next;
            }
        }
    }

    for (; aNode; aNode = aNode->next) result.append(aNode->value);
    for (; bNode; bNode = bNode->next) result.append(bNode->value);

    return result;
}


void timSort(List &list) {
    if (list.getSize() <= 1) return;

    Stack runs = TimSortUtils::getRuns(list);

    List x = runs.pop();
    List y = runs.pop();
    List z = runs.pop();
    while (!runs.isEmpty()) {
        // X > Y + Z && Y > Z
        if ((x.getSize() > y.getSize() + z.getSize()) && (y > z)) {
            x = TimSortUtils::merge(y, x);
            y = z;
            z = runs.pop();
        } else {
            if (x < z) {
                x = TimSortUtils::merge(x, y);
                y = z;
                z = runs.pop();
            } else {
                y = TimSortUtils::merge(z, y);
                z = runs.pop();
            }
        }
    }

    if (!y.isEmpty()) x = TimSortUtils::merge(x, y);
    if (!z.isEmpty()) x = TimSortUtils::merge(x, z);

    list = x;
}


#endif