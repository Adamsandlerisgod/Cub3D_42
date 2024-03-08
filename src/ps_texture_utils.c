/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_texture_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:51:55 by jdaly             #+#    #+#             */
/*   Updated: 2024/03/06 19:30:25 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

//check texture type & paths/color codes
int	is_valid_texture_type(char *mapdir)
{
	const char	*valid_directions[] = {"NO", "SO", "EA", "WE", "C", "F"};
	int			i;

	i = 0;
	while (i < 6)
	{
		if (ft_strcmp(mapdir, valid_directions[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

//color codes
int	is_valid_color_code(char *color)
{
	int	i;

	i = 0;
	while (color[i])
	{
		if (!ft_isdigit(color[i]))
			return (0);
		i++;
	}
	if (ft_atoi(color) > 255)
		return (0);
	return (1);
}

int	is_valid_color_path(char *path)
{
	int		i;
	char	**color;

	color = ft_split(path, ',');
	if (count_array_elements(color) != 3)
		return (free_array(color), err_msg(path, "f/c color", FAILURE));
	i = 0;
	while (i < 3)
	{
		if (!is_valid_color_code(color[i]))
			return (free_array(color), err_msg(path, "f/c code", FAILURE));
		i++;
	}
	free_array(color);
	return (SUCCESS);
}

int	is_valid_texture_path(char type, char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (type == 'N' || type == 'S' || type == 'E' || type == 'W')
	{
		if (fd == -1)
			return (err_msg(path, strerror(errno), FAILURE));
		close(fd);
	}
	else if (type == 'F' || type == 'C')
		return (is_valid_color_path(path));
	else
		return (FAILURE);
	return (SUCCESS);
}
