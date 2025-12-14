#ifndef	PARSING_CUB_H
#define	PARSING_CUB_H

# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_cred_list
{
	char						*content;
	struct s_cred_list	*next;
}	t_cred_list;

typedef struct s_map t_map;

t_cred_list	*grap_credantials(int fd);
char		*get_wanted_line(t_cred_list *list, char *wanted);
void		print_td(char **str);
int			a_valid_argb(char *str);
int			check_content_order(t_cred_list *list);
int			asign_colors(t_cred_list *list, t_map **cb_st);
int			extract_credantials(t_map **cb_st, int fd);
int			asign_texters(t_cred_list *list, t_map **cub);
int			check_dup(t_cred_list *list, char *to_check);
int			missing_or_dup(t_cred_list *list);
int 		td_len(char **td);
int			parse_arguments(t_map **cb_st, char **av);
int			add_content(t_cred_list **list, char *content);
int			empty_line(char *line);

void		player_spwn_or(char s, t_map **cub);
void		player_position(char **map, t_map **cub);
int			parse_map(char **map, t_map **cb_st, t_cred_list *list);
int			get_largest_row(t_cred_list *list);
char		*equal_rows(char *line_map, int len);
char		**dup_map(char **map, t_cred_list *list);
int			get_map(t_cred_list *list, t_map **cub);
int 		valid_map_arg(char *arg);
int			one_player_on_map(char **map);
int			cub_items(char *line);
int 		is_player(char c);
int			closed_map(char **map);
int			is_map_line(char *line);
int 		valid_map_arg(char *arg);
int			map_size(t_cred_list *list);
int			asign_map(t_cred_list *list, t_map **cub);

#endif