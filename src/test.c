// void executeCommands(SimpleCommand* commands) {
//     while (commands != NULL) {
//         pid_t pid = fork();

//         if (pid == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         } else if (pid == 0) {
//             execvp(commands->command, commands->command_arguments);
//             perror("execvp");
//             exit(EXIT_FAILURE);
//         } else {
//             waitpid(pid, NULL, 0);
//             commands = commands->next;
//         }
//     }
// }
