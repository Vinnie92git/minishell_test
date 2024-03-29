/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vini <vini@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:53:30 by vipalaci          #+#    #+#             */
/*   Updated: 2024/03/06 21:09:08 by vini             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --- LIBRARIES --- */
# include "../libft/include/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h> 
# include <sys/stat.h>
# include <errno.h>
# include <readline/readline.h>	//función readline -prompt-
# include <readline/history.h>	//readline() antiguo
# include <signal.h> 			//función signal() / sigaction()
# include <termios.h>			//función tcsetattr() para ctrl+c '^C'

/* ------ STRUCTS ------ */
typedef struct s_token	t_token;
typedef struct s_info	t_info;
typedef struct s_scmd	t_scmd;

typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_info
{
	int				pipe_nbr;
	char			*path;
	char			**bin_paths;
	char			**env_cpy;
}	t_info;

typedef struct s_scmd
{
	int				infile;
	int				outfile;
	int				heredoc;
	char			*cmd_name;
	char			*cmd_path;
	char			**cmd_args;
	t_token			*wordlist;
	struct s_scmd	*next;
}	t_scmd;

/* ------ ENUMS ------ */
enum e_boolean
{
	FALSE = 0,
	TRUE,
};

enum e_tokens
{
	IN_REDIR = 2,
	OUT_REDIR,
	HEREDOC,
	APPEND,
	PIPE,
	WORD,
	QUOTED_WORD,
	FILENAME,
	EOF_N
};

enum e_quotes
{
	SINGLE_QUOTE = 11,
	DOUBLE_QUOTE
};

enum e_error
{
	INIT_INT = 13,
	QUOTING_ERR,
	READLINE_ERR,
	PARSE_ERR,
	INFILE_ERR,
	OUTFILE_ERR,
	MALLOC_ERR,
	COMMAND_ERR,
	PIPE_ERR,
	FORK_ERR
};

/* ------ GLOBAL ------ */
extern int	exit_status;

/* ------ MAIN ------ */
void	shell_operation(char *line, t_token *list, t_scmd *scmds, t_info info);

/* ------ LEXER ------ */
int		lexer(t_token **token_list, char *input);
int		handle_operators(t_token **token_list, char *input, int i);
int		handle_words(t_token **token_list, char *input, int i);
int		operator_type(char *input, int i);
int		is_operator(char c);
int		is_qte(char c);
int		is_space(char c);
int		is_dsign(char c);

/* ------ PARSER ------ */
t_token	*create_scmd(t_token *token, t_scmd **scmds_list);
void	create_node(t_token *token, t_token **wordlist);
void	store_cmdargs(t_scmd *scmd);
void	handle_redir(t_scmd **scmds_list);
void	assign_filenames(t_token **token_list);
void	expand_var(t_scmd **scmds_list, char **env);
void	check_dsign(t_scmd *scmd, char **env);
void	remove_quotes(t_scmd **scmds_list);
void	check_quotes(t_scmd *scmd);
char	*unquoted_str(char *unquoted, char *str, int i, int j);
char	*unquote(char *str);
char	*expand(char *str, char **env);
char	*buffer_var(char *source, int start, int end, char **env);
char	*expand_dsign(char *str, char **env, int start);
char	*quoted_dsign(char *str, char **env, int i);
int		count_flen(char *str, int i);
int		closing_quote(char *str, int i);
int		build_cmd(t_scmd *scmd);
int		find_cmds(t_scmd **scmds_list);
int		open_heredoc(t_scmd *scmd, t_token *token);
int		open_append(t_scmd *scmd, t_token *token);
int		open_outfile(t_scmd *scmd, t_token *token);
int		open_infile(t_scmd *scmd, t_token *token);
int		check_files(t_scmd *scmd);
int		build_scmdlist(t_token **token_list, t_scmd **scmds_list, t_info *info);
int		is_redir(int type);
int		check_pipe(t_token *token);
int		check_redir(t_token *token);
int		check_syntax(t_token **token_list);
int		parser(t_token **token_list, t_scmd **scmds_list, t_info *info);

/* ------ EXECUTER ------ */
void	ft_dup(int old_fd, int new_fd);
void	check_cmds(t_scmd **scmds_list, t_info *info);
void	exec_child(t_scmd *scmd, t_info *info, int upstream, int *pipe_fd);
void	last_child(t_scmd *scmd, t_info *info, int upstream);
void	ft_builtin(char **args);
void	parent_close(int fd_1, int fd_2, t_scmd *scmd);
int		check_builtin(t_scmd *scmd);
int		exec_command(t_scmd *scmd, t_info *info, int upstream, int *pipe_fd);
int		last_command(t_scmd *scmd, t_info *info, int upstream);
int		exec_cmds(t_scmd **scmds_list, t_info *info);
int		get_cmd(t_scmd *scmds_list, t_info *info);
int		check_path(t_scmd *scmd);
int		executer(t_scmd **scmds_list, t_info *info);

/* ------ LISTS ------ */
t_token	*ms_lstnew(void);
t_scmd	*ms_cmdnew(void);
void	ms_cmdadd_back(t_scmd **list, t_scmd *new);
void	ms_lstadd_back(t_token **list, t_token *new);
void	ms_lstclear(t_token **list);
void	ms_cmdclear(t_scmd **list);
void	ms_print_lst(t_token *token);
void	ms_print_cmdlst(t_scmd *sequence);
void	ms_close_fds(t_scmd **list);

/* ------ ERROR ------ */
void	panic(int err, t_token **list, t_token *token);
void	free_array(char **str);
void	free_info(t_info info);

/* ------ ENV ------ */
char	**copy_env(char **envp);
char	*get_path(char **env);
char	*find_var(char *varname, char **env);

#endif
