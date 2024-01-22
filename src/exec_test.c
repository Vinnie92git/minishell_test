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



// fd_out / fd_in = open_file(file, redir);

// int	open_file(char *file, int in_or_out)
// {
// 	int	ret;

// 	if (in_or_out == 0)
// 		ret = open(file, O_RDONLY, 0777);
// 	if (in_or_out == 1)
// 		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	if (in_or_out == 2)
// 		ret = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	if (ret == -1)
// 		exit(0);
// 	return (ret);
// }