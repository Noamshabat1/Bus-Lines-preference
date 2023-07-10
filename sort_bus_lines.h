#ifndef EX2_REPO_SORTBUSLINES_H
#define EX2_REPO_SORTBUSLINES_H
// write only between #define EX2_REPO_SORTBUSLINES_H and #endif
// EX2_REPO_SORTBUSLINES_H
#include <string.h>
#define NAME_LEN 21

/**
 * A BusLine struct containing: name of the line, line number + distance
 * from the campus and duration to get to the campus
 */
typedef struct BusLine
{
    char name[NAME_LEN];
    int distance, duration;
} BusLine;

/**
 * A enum containing two definitions: DISTANCE = 0 and DURATION = 1.
 */
typedef enum SortType
{
    DISTANCE,
    DURATION
} SortType;

/**
 * Implementation of Bubble Sort.
 * this kind of implementation for Bubble Sort algorithm is using pointers
 * only.
 *
 * @param start the start of the array to sort
 * @param end the end of the array to sort
 */
void bubble_sort (BusLine *start, BusLine *end);

/**
 * Implementation of Quick Sort.
 * this kind of implementation for Quick Sort algorithm is using pointers
 * only.
 *
 * @param start the start of the array to sort
 * @param end the end of the array to sort
 */
void quick_sort (BusLine *start, BusLine *end, SortType sort_type);

/**
 * Implementation of partition affect for Quick Sort - for swapping two
 * given pointers.
 *
 * @param start first given pointer
 * @param end second given pointer
 * @param sort_type the type of the
 */

BusLine *partition (BusLine *start, BusLine *end, SortType sort_type);
/**
 * Returns the number of items between start and end
 *
 * @param start the start of the given array
 * @param end the end of the given array
 */
long input_size (BusLine *start, BusLine *end);

/**
 * Implementation of swapping affect for Quick Sort & Bubble Sort
 * - for swapping two given pointers.
 *
 * @param start first given pointer
 * @param end second given pointer
 */
void swap (BusLine *start, BusLine *end);

/**
 * Implementation of
 *
 * @param sort_type
 * @param bus_line
 */
int get_value (SortType sort_type, BusLine *bus_line);

#endif //EX2_REPO_SORTBUSLINES_H
