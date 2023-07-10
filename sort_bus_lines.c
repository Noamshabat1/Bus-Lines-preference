#include "sort_bus_lines.h"

void swap (BusLine *xp, BusLine *yp)
{
  BusLine temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int get_value (SortType sort_type, BusLine *bus_line)
{
  if (sort_type == DURATION)
  {
    return bus_line->duration;
  }
  return bus_line->distance;
}

BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{
  long len = input_size (start, end);
  long pivot_move = len - 1;
  int index = -1;
  for (int k = 0; k < len - 1; k++)
  {
    if (get_value (sort_type, start + k)
        <= get_value (sort_type, start + pivot_move))
    {
      index++;
      swap (start + index, start + k);
    }
  }

  swap (start + index + 1, start + pivot_move);
  BusLine *res = start + index + 1;
  return res;
}

long input_size (BusLine *start, BusLine *end)
{
  return end - start;
}

void bubble_sort (BusLine *start, BusLine *end)
{
  long length_of_input = input_size (start, end);

  for (int i = 0; i < length_of_input; i++)
  {
    for (int k = 0; k < (length_of_input - i - 1); k++)
    {
      if (strcmp ((*(start + k)).name, (*(start + k + 1)).name) > 0)
      {
        swap (start + k, start + k + 1);
      }
    }
  }
}

void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{
  if (start < end)
  {
    BusLine *middle = partition (start, end, sort_type);
    quick_sort (start, middle, sort_type);
    quick_sort (middle + 1, end, sort_type);
  }
}