#ifndef EX2_REPO_TESTBUSLINES_H
#define EX2_REPO_TESTBUSLINES_H
// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
// EX2_REPO_TESTBUSLINES_H
#include "sort_bus_lines.h"

/**
 * This function is testing when given pointers they are sorted
 * correctly with the implementation of quick-sort.
 *
 * @param start the start of the array.
 * @param end the end of the array.
 *
 * @return: 0 if succeed or 1 if failed.
 */
int is_sorted_by_distance (BusLine *start, BusLine *end);

/**
 * This function is testing when given pointers they are sorted
 * correctly with the implementation of quick-sort.
 *
 * @param start the start of the array.
 * @param end the end of the array.
 *
 * @return: 0 if succeed or 1 if failed.
 */
int is_sorted_by_duration (BusLine *start, BusLine *end);

/**
 * This function is testing when given pointers they are sorted
 * correctly with the implementation of bubble-sort.
 *
 * @param start the start of the array.
 * @param end the end of the array.
 *
 * @return: 0 if succeed or 1 if failed.
 */
int is_sorted_by_name (BusLine *start, BusLine *end);

/**
 * This function is testing when given 4 pointers which they are a copy of
 * each other one is sorted and the other is not changed that they are in
 * fact the same with different in order.
 * they are the
 * correctly with the implementation of quick-sort.
 *
 * @param start_sorted the start of the tested array.
 * @param end_sorted the end of the tested array.
 * @param start_original the start of the original array.
 * @param end_original the end of the original array.
 *
 * @return: 0 if they are the same or 1 if not.
 */
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original);

/**
 * Returns the number of items between start and end
 *
 * @param start the start of the given array
 * @param end the end of the given array
 */
long input_size (BusLine *start, BusLine *end);

// write only between #define EX2_REPO_TESTBUSLINES_H and #endif
// EX2_REPO_TESTBUSLINES_H
#endif //EX2_REPO_TESTBUSLINES_H
