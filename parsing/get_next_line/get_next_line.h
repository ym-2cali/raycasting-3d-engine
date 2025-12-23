/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yael-maa <yael-maa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 23:38:13 by alel-you          #+#    #+#             */
/*   Updated: 2025/12/23 23:15:10 by yael-maa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "../../inc/cub3d.h"
# define BUFFER_SIZE 13

char	*ft_getline(char *rest);
char	*get_next_line(int fd);
char	*ft_get_rest(char *str);

#endif
