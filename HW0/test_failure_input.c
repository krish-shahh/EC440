#include "myshell_parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int main(void) {
    struct pipeline *my_pipeline = pipeline_build("ls\n");
  
    // Test that a pipeline was returned
    assert(my_pipeline != NULL);
    assert(!my_pipeline->is_background);
    assert(my_pipeline->commands != NULL);
  
    // Intentionally incorrect test for the parsed args
    // This assertion will fail because the command is "ls", not "wrong_command"
    assert(strcmp("wrong_command", my_pipeline->commands->command_args[0]) == 0);

    // Remaining tests
    assert(my_pipeline->commands->command_args[1] == NULL);
    assert(my_pipeline->commands->redirect_in_path == NULL);
    assert(my_pipeline->commands->redirect_out_path == NULL);
    assert(my_pipeline->commands->next == NULL);
  
    pipeline_free(my_pipeline);
}
