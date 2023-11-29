/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vipalaci <vipalaci@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:53:30 by vipalaci          #+#    #+#             */
/*   Updated: 2023/11/29 13:09:27 by vipalaci         ###   ########.fr       */
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
typedef struct s_inf	t_inf;

typedef struct s_token
{
	int				type;
	char			*content;
	struct s_token	*next;
}	t_token;

typedef struct s_inf
{
	t_token	*token_list;
}	t_inf;

/* ------- DEFINES ------- */
// #define INIT_INT		-1  //TOKEN_TYPE & OTHER ERRORS
// #define FALSE			0	//BOOLEAN
// #define TRUE			1	//BOOLEAN
// #define SQ_WORD			2	//SINGLE QUOTED STRING
// #define DQ_WORD			3	//DOUBLE QUOTED STRING
// #define GREAT			4	//'>'
// #define LESS			5	//'<'
// #define APPEND			6	//'>>'
// #define HEREDOC			7	//'<<'
// #define GREATAMPERSAND	8	//'>&'
// #define PIPE			9	//'|'
// #define END				10	//'\0'

/* ------- ERRORS ------- */
// #define QUOTING_ERR		11

enum boolean {
	FALSE,
	TRUE,
};

enum tokens {
	IN_REDIR,
	OUT_REDIR,
	HEREDOC,
	APPEND,
	PIPE,
	WORD
};

enum quotes {
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	SQ_WORD,
	DQ_WORD
};

enum error {
	INIT_INT,
	QUOTING_ERR
};

#endif
