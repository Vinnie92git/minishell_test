/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:53:30 by vipalaci          #+#    #+#             */
/*   Updated: 2024/02/13 15:20:21 by vipalaci         ###   ########.fr       */
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
	FILENAME
};

enum e_quotes
{
	SINGLE_QUOTE = 10,
	DOUBLE_QUOTE
};

enum e_error
{
	INIT_INT = 12,
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

/* ------ LEXER ------ */
int		lexer(t_token **token_list, char *input, char **env);
int		handle_quotes(t_token **token_list, char *input, int i, char **env);
int		handle_operators(t_token **token_list, char *input, int i);
int		handle_words(t_token **token_list, char *input, int i);
int		handle_dsign(t_token **token_list, char *input, int i, char **env);
int		operator_type(char *input, int i);
int		is_operator(char c);
int		is_quote(char c);
int		is_space(char c);
int		is_dsign(char c);
char	*quoted_dsign(char *str, char **env);
char	*expand(char *source, int start, int end, char **env);
char	*find_var(char *var, char **env);

/* ------ PARSER ------ */
t_token	*create_scmd(t_token *token, t_scmd **scmds_list);
void	create_node(t_token *token, t_token **wordlist);
void	store_cmdargs(t_scmd *scmd);
int		build_cmd(t_scmd *scmd);
int		find_cmds(t_scmd **scmds_list);
int		open_heredoc(t_scmd *scmd, t_token *token);
int		open_append(t_scmd *scmd, t_token *token);
int		open_outfile(t_scmd *scmd, t_token *token);
int		open_infile(t_scmd *scmd, t_token *token);
int		check_files(t_scmd *scmd);
int		handle_redir(t_scmd **scmds_list);
int		build_scmdlist(t_token **token_list, t_scmd **scmds_list, t_info *info);
int		is_redir(int type);
int		check_pipe(t_token *token);
int		check_redir(t_token *token);
int		check_syntax(t_token **token_list);
int		parser(t_token **token_list, t_scmd **scmds_list, t_info *info);

/* ------ EXECUTER ------ */
int		create_child(t_scmd *scmd, t_info *info);
int		single_child(t_scmd *scmd, t_info *info);
int		exec_cmds(t_scmd **scmds_list, t_info *info);
int		get_cmd(t_scmd *scmds_list, t_info *info);
int		check_path(t_scmd *scmd);
int		check_cmds(t_scmd **scmds_list, t_info *info);
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

/* ------ ENV ------ */
char	**copy_env(char **envp);
char	*get_path(char **env);

#endif
