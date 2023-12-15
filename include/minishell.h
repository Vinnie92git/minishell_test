/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:53:30 by vipalaci          #+#    #+#             */
/*   Updated: 2023/12/15 14:50:16 by vipalaci         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* --- LIBRARIES --- */
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

typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
}	t_token;

/* ------ ENUMS ------ */
enum e_boolean {
	FALSE = 0,
	TRUE,
};

enum e_tokens {
	IN_REDIR = 2,
	OUT_REDIR,
	HEREDOC,
	APPEND,
	PIPE,
	WORD
};

enum e_quotes {
	SINGLE_QUOTE = 8,
	DOUBLE_QUOTE,
	SQ_WORD,
	DQ_WORD
};

enum e_error {
	INIT_INT = 12,
	QUOTING_ERR,
	READLINE_ERR
};

/* ------ MAIN ------ */
char	**copy_env(char **envp);

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
char	*quoted_dsign(char *input, int i, int end, char **env);

/* ------ PARSER ------ */
void	parser(t_token **token_list);
void	parse_cmd(t_token **token_list);

/* ------ LISTS ------ */
t_token	*ms_lstnew(void);
void	ms_lstadd_back(t_token **list, t_token *new);
void	ms_lstclear(t_token **list);
void	ms_print_lst(t_token *token);
int		ms_check_lst(t_token *token, int type);

/* ------ UTILS ------ */
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char	*s1);
char	*find_var(char *var, char **env);
char	*ft_strchr(char *s, int c);
// void	*ft_memset(void *b, int c, size_t len);

/* ------ ERROR ------ */
void	panic(int err, t_token **list, t_token *token);

#endif
