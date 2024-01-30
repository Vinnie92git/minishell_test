/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:53:30 by vipalaci          #+#    #+#             */
/*   Updated: 2024/01/29 14:26:21 by vipalaci         ###   ########.fr       */
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
	int				*pipes;
	char			*path;
	char			**bin_paths;
	char			**env_cpy;
}	t_info;

typedef struct s_scmd
{
	int				word_count;
	int				arg_count;
	char			*cmd_name;
	char			**cmd_args;
	char			**words;
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
	QUOTED_WORD
};

enum e_quotes
{
	SINGLE_QUOTE = 9,
	DOUBLE_QUOTE
};

enum e_error
{
	INIT_INT = 11,
	QUOTING_ERR,
	READLINE_ERR,
	PARSE_ERR
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
int		build_scmdlist(t_token **token_list, t_scmd **scmds_list, t_info *info);
int		is_redir(int type);
int		check_pipe(t_token *token);
int		check_redir(t_token *token);
int		check_syntax(t_token **token_list);
int		parser(t_token **token_list, t_scmd **scmds_list, t_info *info);

/* ------ LISTS ------ */
t_token	*ms_lstnew(void);
t_scmd	*ms_cmdnew(void);
void	ms_cmdadd_back(t_scmd **list, t_scmd *new);
void	ms_lstadd_back(t_token **list, t_token *new);
void	ms_lstclear(t_token **list);
void	ms_cmdclear(t_scmd **list);
void	ms_print_lst(t_token *token);
void	ms_print_cmdlst(t_scmd *sequence);

/* ------ UTILS ------ */
// size_t	ft_strlen(const char *str);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	*ft_strdup(const char	*s1);
// char	*ft_strjoin_ms(char *s1, char *s2);
// char	*ft_join_ms(char *dest, char *s1, char *s2);

/* ------ ERROR ------ */
void	panic(int err, t_token **list, t_token *token);

/* ------ ENV ------ */
char	**copy_env(char **envp);
char	*get_path(char **env);

#endif
