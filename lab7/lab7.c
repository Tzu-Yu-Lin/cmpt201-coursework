#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUTS 100
#define MAX_LINES 100

typedef struct {
  int line_number;
  int value;
} Input;

typedef struct {
  int line_number;
  int doubled_value;
} IntermediateInput;

typedef struct {
  int doubled_value;
  int line_numbers[MAX_LINES];
  int line_count;
} Output;

void map(Input *input, IntermediateInput *intermediate_input);
void groupByKey(IntermediateInput *input, Output *output, int *result_count);
void reduce(Output *output);

void map(Input *input, IntermediateInput *intermediate_input) {
  intermediate_input->line_number = input->line_number;
  intermediate_input->doubled_value = input->value * 2;
}

void groupByKey(IntermediateInput *input, Output *output, int *result_count) {
  int found = 0;

  for (int i = 0; i < *result_count; i++) {
    if (output[i].doubled_value == input->doubled_value) {
      output[i].line_numbers[output[i].line_count++] = input->line_number;
      found = 1;
      break;
    }
  }

  if (!found) {
    output[*result_count].doubled_value = input->doubled_value;
    output[*result_count].line_numbers[0] = input->line_number;
    output[*result_count].line_count = 1;
    (*result_count)++;
  }
}

void reduce(Output *output) {
  printf("(%d, [", output->doubled_value);
  for (int i = 0; i < output->line_count; i++) {
    printf("%d", output->line_numbers[i]);
    if (i < output->line_count - 1)
      printf(", ");
  }
  printf("])\n");
}

int main() {
  Input inputs[MAX_INPUTS];
  IntermediateInput intermediate[MAX_INPUTS];
  Output outputs[MAX_INPUTS];
  int result_count = 0;

  char buffer[32];
  int input_count = 0;

  printf("Enter values (one per line). Type 'end' to finish:\n");

  while (1) {
    if (!fgets(buffer, sizeof(buffer), stdin))
      break;
    if (strncmp(buffer, "end", 3) == 0)
      break;

    int value = atoi(buffer);
    inputs[input_count].line_number = input_count + 1;
    inputs[input_count].value = value;
    input_count++;
  }

  for (int i = 0; i < input_count; i++) {
    map(&inputs[i], &intermediate[i]);
  }

  for (int i = 0; i < input_count; i++) {
    groupByKey(&intermediate[i], outputs, &result_count);
  }

  for (int i = 0; i < result_count; i++) {
    reduce(&outputs[i]);
  }

  return 0;
}
