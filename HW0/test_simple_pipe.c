#include "myshell_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int
main(void)
{
  struct pipeline* my_pipeline = pipeline_build("ls | cat\n");
  
  // Test that a pipeline was returned
  assert(my_pipeline != NULL);
  assert(!my_pipeline->is_background);
  assert(my_pipeline->commands != NULL);
  
  // Test the parsed args
  assert(strcmp("ls", my_pipeline->commands->command_args[0]) == 0);
  assert(my_pipeline->commands->command_args[1] == NULL);
  
  // Test the redirect state
  assert(my_pipeline->commands->redirect_in_path == NULL);
  assert(my_pipeline->commands->redirect_out_path == NULL);
  
  // Test that there are multiple parsed command in the pipeline
  assert(my_pipeline->commands->next != NULL);

  // Test the parsed args for the second command
  struct pipeline_command *second_command = my_pipeline->commands->next;
  assert(strcmp("cat", second_command->command_args[0]) == 0);
  assert(second_command->command_args[1] == NULL);

  // Test the redirect state for the second command
  assert(second_command->redirect_in_path == NULL);
  assert(second_command->redirect_out_path == NULL);

  // Test that there is no further command in the pipeline
  assert(second_command->next == NULL);
  
  // keep going... what should we be testign next?
  pipeline_free(my_pipeline);
}
