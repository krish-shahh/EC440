#include "myshell_parser.h"
#include "stddef.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pipeline *pipeline_build(const char *command_line) {
    struct pipeline *new_pipeline = malloc(sizeof(struct pipeline));
    if (!new_pipeline) return NULL;

    new_pipeline->commands = NULL;
    new_pipeline->is_background = false;

    char *line = strdup(command_line); // Duplicate command_line for strtok
    char *token = strtok(line, " \t\n");
    struct pipeline_command **next_cmd = &(new_pipeline->commands);

    while (token != NULL) {
        if (*next_cmd == NULL) {
            *next_cmd = malloc(sizeof(struct pipeline_command));
            memset(*next_cmd, 0, sizeof(struct pipeline_command));
        }

        if (strcmp(token, "|") == 0) {
            next_cmd = &((*next_cmd)->next);
        } else if (strcmp(token, "&") == 0) {
            new_pipeline->is_background = true;
        } else if (strcmp(token, "<") == 0) {
            token = strtok(NULL, " \t\n");
            (*next_cmd)->redirect_in_path = strdup(token);
        } else if (strcmp(token, ">") == 0) {
            token = strtok(NULL, " \t\n");
            (*next_cmd)->redirect_out_path = strdup(token);
        } else {
            // Add to command_args
            int i = 0;
            while ((*next_cmd)->command_args[i] != NULL) i++;
            (*next_cmd)->command_args[i] = strdup(token);
        }

        token = strtok(NULL, " \t\n");
    }

    free(line);
    return new_pipeline;
}

void pipeline_free(struct pipeline *pipeline) {
    struct pipeline_command *cmd = pipeline->commands;
    while (cmd != NULL) {
        struct pipeline_command *next_cmd = cmd->next;

        for (int i = 0; cmd->command_args[i] != NULL; i++) {
            free(cmd->command_args[i]);
        }

        free(cmd->redirect_in_path);
        free(cmd->redirect_out_path);
        free(cmd);
        cmd = next_cmd;
    }

    free(pipeline);
}
