#include "test_bus_lines.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_sorted_by_distance (BusLine *start, BusLine *end)
{
  long length = input_size (start, end);
  for (int i = 0; i < length - 1; i++)
  {
    if ((start + i)->distance > (start + i + 1)->distance)
    {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int is_sorted_by_duration (BusLine *start, BusLine *end)
{
  long length = input_size (start, end);
  for (int i = 0; i < length - 1; i++)
  {
    if ((start + i)->duration > (start + i + 1)->duration)
    {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int is_sorted_by_name (BusLine *start, BusLine *end)
{
  long length = input_size (start, end);
  for (int i = 0; i < length - 1; i++)
  {
    if (strcmp ((start + i)->name, (start + i + 1)->name) > 0)
    {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int is_equal (BusLine *start_sorted, BusLine *end_sorted,
              BusLine *start_original, BusLine *end_original)
{
  int i;
  for (i = 0; (start_original + i) < end_original; i++)
  {
    bool found_the_bus = false;
    for (int j = 0; (start_sorted + j) < end_sorted; j++)
    {
      if (strcmp ((start_original + i)->name, (start_sorted + j)->name) == 0)
      {
        if ((start_original + i)->distance == (start_sorted + j)->distance)
        {
          if ((start_original + i)->duration == (start_sorted + j)->duration)
          {
            found_the_bus = true;
            break;
          }
        }
      }
    }
    if (!found_the_bus)
    {
      break;
    }
  }
  if ((start_original + i) < end_original)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
