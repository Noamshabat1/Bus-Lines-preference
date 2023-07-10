#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 60
#define SINGLE_MAX_LENGTH 20
#define ALPHABET_LOWER_START 'a'
#define ALPHABET_LOWER_END 'z'
#define NUMBERS_LOWER_START '0'
#define NUMBERS_LOWER_END '9'
#define NUMBER_OF_INPUT 3
#define BIGGEST_FOR_DISTANCE 1000
#define SMALLEST_FOR_DISTANCE 0
#define BIGGEST_FOR_DURATION 100
#define SMALLEST_FOR_DURATION 10

#define TEST_COMMEND "test"
#define SORT_BY_DURATION "by_duration"
#define SORT_BY_DISTANCE "by_distance"
#define SORT_BY_NAME "by_name"

// ERROR MESSAGE'S SECTION:

#define ERR_MSG_CLI_ARGS "ERROR: the program has receives unexpected " \
"number of arguments.\n"
#define ERR_MSG_INVALID_CMD "ERROR: you have insert incorrect commend.\n"
#define ERR_MSG_COMPILATION_FGETS "ERROR: The fgest method haven't worked.\n"
#define ERR_MSG_COMPILATION_SSCANF "ERROR: The sscanf method haven't worked.\n"
#define ERR_MSG_NUMBER_OF_LINES "ERROR: the program has receives empty" \
" or negative amount of commends.\n"
#define ERR_MSG_LINE_NAME "ERROR: you have insert one or more incorrect" \
" characters to the name you have chosen.\n"
#define ERR_MSG_DISTANCE "ERROR: the given range is out of limit.\n"
#define ERR_MSG_DURATION "ERROR: the given range is invalid.\n"


// COMPILATION & DECLARATION SECTION:

int validate_input (int argc, char *argv[]);
int run_all_tests (BusLine *start, BusLine *end, int number_of_lines);
int validate_buses (BusLine **data_ptr, int *number_of_lines);
int check_number_of_lines (int number_of_line);
int check_bus (char *line_name, int distance, int duration);
void print_output (BusLine *start, BusLine *end);

/**
 * The main function for running the sort_lines program.
 * This program is using two different sorting algorithms, Bubble-sort &
 * Quick-sort inorder to map-out the best path regarding to the commend
 * given in order to get to the best path.
 *
 * @param argc number of arguments inserted
 * @param argv array of arguments inserted
 *
 * @return 0 if the program ends successfully, 1 otherwise
 */
int main (int argc, char *argv[])
{

  if (validate_input (argc, argv) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  int number_of_lines;
  BusLine *bus_lines_data = NULL;
  if (validate_buses (&bus_lines_data, &number_of_lines) == EXIT_FAILURE)
  {
    // no need to do free
    return EXIT_FAILURE;
  }

  if (strcmp (argv[1], SORT_BY_DISTANCE) == 0)
  {
    quick_sort (bus_lines_data, bus_lines_data + number_of_lines, DISTANCE);
    print_output (bus_lines_data, bus_lines_data + number_of_lines);
  }
  else if (strcmp (argv[1], SORT_BY_DURATION) == 0)
  {
    quick_sort (bus_lines_data, bus_lines_data + number_of_lines, DURATION);
    print_output (bus_lines_data, bus_lines_data + number_of_lines);
  }
  else if (strcmp (argv[1], SORT_BY_NAME) == 0)
  {
    bubble_sort (bus_lines_data, bus_lines_data + number_of_lines);
    print_output (bus_lines_data, bus_lines_data + number_of_lines);
  }
  else
  {
    run_all_tests (bus_lines_data, bus_lines_data + number_of_lines,
                   number_of_lines);
  }

  free (bus_lines_data);
  return EXIT_SUCCESS;
}

int validate_input (int argc, char *argv[])
{
  if (argc != 2)
  {
    fprintf (stdout, ERR_MSG_CLI_ARGS); // check about it
    return EXIT_FAILURE;
  }
  char *commend = argv[1];
  if (strcmp (commend, SORT_BY_DURATION) == 0
      || strcmp (commend, SORT_BY_DISTANCE) == 0
      || strcmp (commend, SORT_BY_NAME) == 0
      || strcmp (commend, TEST_COMMEND) == 0)
  {
    return EXIT_SUCCESS;
  }
  fprintf (stdout, ERR_MSG_INVALID_CMD);
  return EXIT_FAILURE;
}

int validate_number_of_lines (int *number_of_lines)
{
  fprintf (stdout, "Enter number of lines. Then enter\n");
  char buffer[MAX_LENGTH];
  if (fgets (buffer, MAX_LENGTH, stdin) == NULL)
  {
    fprintf (stdout, ERR_MSG_COMPILATION_FGETS);
    return EXIT_FAILURE;
  }

  if (sscanf (buffer, "%d", number_of_lines) != 1) // strtol instead of?
  {
    fprintf (stdout, ERR_MSG_COMPILATION_SSCANF);
    return EXIT_FAILURE;
  }
  if (check_number_of_lines (*number_of_lines) == EXIT_FAILURE)
  {
    fprintf (stdout, ERR_MSG_NUMBER_OF_LINES);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int validate_bus_info (char *line_name, int *distance, int *duration)
{
  fprintf (stdout, "Enter line info. Then enter\n");
  // bus_info
  char buffer[MAX_LENGTH];
  if (fgets (buffer, MAX_LENGTH, stdin) == NULL)
  {
    fprintf (stdout, ERR_MSG_COMPILATION_FGETS);
    return EXIT_FAILURE;
  }
  if (sscanf (buffer, "%20[^,],%d,%d", line_name, distance, duration)
      != NUMBER_OF_INPUT)
  {
    fprintf (stdout, ERR_MSG_COMPILATION_SSCANF);
    return EXIT_FAILURE;
  }
  if (check_bus (line_name, *distance, *duration) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int validate_buses (BusLine **data_ptr, int *number_of_lines)
{
  if (validate_number_of_lines (number_of_lines) == EXIT_FAILURE)
  {
    return EXIT_FAILURE;
  }

  int counter_success = 0;
  *data_ptr = malloc ((*number_of_lines) * sizeof (BusLine));
  if (*data_ptr == NULL)
  {
    return EXIT_FAILURE;
  }

  while (counter_success < *number_of_lines)
  {
    char line_name[SINGLE_MAX_LENGTH];
    int distance;
    int duration;
    if (validate_bus_info (line_name, &distance, &duration) == EXIT_SUCCESS)
    {
      strcpy ((*data_ptr)[counter_success].name, line_name);
      (*data_ptr)[counter_success].distance = distance;
      (*data_ptr)[counter_success].duration = duration;
      counter_success++;
    }
  }
  return EXIT_SUCCESS;
}

int check_number_of_lines (int number_of_lines)
{
  if (number_of_lines <= 0)
  {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int check_bus (char *line_name, int distance, int duration)
{
  for (size_t i = 0; i < strlen (line_name); i++)
  {
    if (!((ALPHABET_LOWER_START <= line_name[i]
           && line_name[i] <= ALPHABET_LOWER_END)
          ||
          (NUMBERS_LOWER_START <= line_name[i]
           && line_name[i] <= NUMBERS_LOWER_END)))
    {
      fprintf (stdout, ERR_MSG_LINE_NAME);
      return EXIT_FAILURE;
    }
  }
  if (!(SMALLEST_FOR_DISTANCE <= distance
        && distance <= BIGGEST_FOR_DISTANCE))
  {
    fprintf (stdout, ERR_MSG_DISTANCE);
    return EXIT_FAILURE;
  }

  if (!(SMALLEST_FOR_DURATION <= duration && duration <= BIGGEST_FOR_DURATION))
  {
    fprintf (stdout, ERR_MSG_DURATION);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void check_test_1 (BusLine *start_cp, BusLine *end_cp, BusLine *start_og,
                   BusLine *end_og)
{
  quick_sort (start_cp, end_cp, DISTANCE);

  int test1 = is_sorted_by_distance (start_cp, end_cp);
  if (test1 == EXIT_FAILURE)
  {
    printf ("FAILED: 1 TEST\n");
  }
  else
  {
    printf ("PASSED: 1 TEST\n");
  }

  int test2 = is_equal (start_cp, end_cp, start_og, end_og);
  if (test2 == EXIT_FAILURE)
  {
    printf ("FAILED: 2 TEST\n");
  }
  else
  {
    printf ("PASSED: 2 TEST\n");
  }
}

void check_test_2 (BusLine *start_cp, BusLine *end_cp, BusLine *start_og,
                   BusLine *end_og)
{

  quick_sort (start_cp, end_cp, DURATION);

  int test3 = is_sorted_by_duration (start_cp, end_cp);
  if (test3 == EXIT_FAILURE)
  {
    printf ("FAILED: 3 TEST\n");
  }
  else
  {
    printf ("PASSED: 3 TEST\n");
  }

  int test4 = is_equal (start_cp, end_cp, start_og, end_og);
  if (test4 == EXIT_FAILURE)
  {
    printf ("FAILED: 4 TEST\n");
  }
  else
  {
    printf ("PASSED: 4 TEST\n");
  }

}

void check_test_3 (BusLine *start_cp, BusLine *end_cp, BusLine *start_og,
                   BusLine *end_og)
{
  bubble_sort (start_cp, end_cp);

  int test5 = is_sorted_by_name (start_cp, end_cp);
  if (test5 == EXIT_FAILURE)
  {
    printf ("FAILED: 5 TEST\n");
  }
  else
  {
    printf ("PASSED: 5 TEST\n");
  }

  int test6 = is_equal (start_cp, end_cp, start_og, end_og);
  if (test6 == EXIT_FAILURE)
  {
    printf ("FAILED: 6 TEST\n");
  }
  else
  {
    printf ("PASSED: 6 TEST\n");
  }
}

int run_all_tests (BusLine *start_og, BusLine *end_og, int number_of_lines)
{
  BusLine *start_cp = malloc (number_of_lines * sizeof (BusLine));
  if (start_cp == NULL)
  {
    return EXIT_FAILURE;
  }
  memcpy (start_cp, start_og, number_of_lines * sizeof (BusLine));

  BusLine *end_cp = start_cp + number_of_lines;

  check_test_1 (start_cp, end_cp, start_og, end_og);

  check_test_2 (start_cp, end_cp, start_og, end_og);

  check_test_3 (start_cp, end_cp, start_og, end_og);

  return EXIT_SUCCESS;
}

void print_output (BusLine *start, BusLine *end)
{
  for (int i = 0; i + start < end; i++)
  {
    BusLine cur = *(start + i);
    printf ("%s,%d,%d\n", cur.name, cur.distance, cur.duration);
  }
}
