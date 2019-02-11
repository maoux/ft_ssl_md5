/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heynard <heynard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 22:32:56 by heynard           #+#    #+#             */
/*   Updated: 2019/02/11 10:09:18 by heynard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <fcntl.h>
# include <limits.h>
# include "../libft/includes/libft.h"

enum				e_options
{
	FLAG_p = 1 << 0,
	FLAG_q = 1 << 1,
	FLAG_r = 1 << 2,
	FLAG_s = 1 << 3,
	FLAG__ = 1 << 4
};

struct				s_command
{
	char		*name;
	int			(*command)(char *, int, char **, char *(*f)(char *, uint64_t));
	char		*(*algo)(char *, uint64_t);
};

/*
** name : command name
** std_in / p : flag to know if we will have to get stdin
** opt : int on which we apply bits masks to store options
** exit_value : -
** arg : pointer on saved argument of argv
** size : size of last read
** code : tool to read fd and store last block size
*/

struct				s_cmd_var
{
	char		*name;
	uint8_t		std_in;
	uint8_t		std_in_p;
	uint8_t		opt;
	int			exit_value;
	char		*arg;
	uint64_t	size;
	int			code;
};

typedef struct s_command	t_command;
typedef struct s_cmd_var	t_cmd_var;

extern t_command	g_commands[];

int					digest_prog(char *str, int ac, char **av,
						char *(*f)(char *, uint64_t));

char				*sum_md5(char *data, uint64_t size);
char				*sum_sha256(char *data, uint64_t size);

int					usage_options(t_cmd_var *var, char wrong_opt);
int					usage_option_s(t_cmd_var *var);

int					get_nb_commands(void);
int					get_command_index(char *cmd, int nbc);

t_cmd_var			*init_cmd_var(void);
int					free_cmd_var(t_cmd_var *var);

int					handle_next_arg(t_cmd_var *var, char *arg,
						char *(*f)(char *, uint64_t));
char				*get_data(t_cmd_var *var, unsigned int fd);
void				print_digest(t_cmd_var *var, int fd, int flag,
						char *(*f)(char *, uint64_t));
char				*malloc_failed(void *data, const char *algo);
char				*malloc_failed_md5(void *data);
char				*malloc_failed_sha256(void *data);

char				*ft_memjoin(char *s1, char *s2, int s1_s, int s2_s);
char				*pad_data(char *data, char *data_w_pad,
						uint64_t size, int endian);
uint32_t			ch(uint32_t x, uint32_t y, uint32_t z);
uint32_t			maj(uint32_t x, uint32_t y, uint32_t z);
uint32_t			sig0(uint32_t x);
uint32_t			sig1(uint32_t x);
uint32_t			sig2(uint32_t x);
uint32_t			sig3(uint32_t x);

#endif
