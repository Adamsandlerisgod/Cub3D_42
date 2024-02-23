/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_init_grid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 19:31:31 by justindaly        #+#    #+#             */
/*   Updated: 2024/02/23 19:27:57 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	get_height_from_map(char **map)
{
	int	i;

	if (map == NULL)
		return (-1);
	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

int	len_no_space_trail(char *str)
{
	int	len;

	if (!str)
		return (-1);
	len = ft_strlen(str);
	if (len == 0)
		return (0);
	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
		len--;
	return (len);
}

int	get_width_from_map(char **map)
{
	int	i;
	int	max_width;
	int	trimmed_len;

	if (map == NULL)
		return (-1);
	max_width = 0;
	i = 0;
	while (map[i] != NULL)
	{
		trimmed_len = len_no_space_trail(map[i]);
		if (trimmed_len > max_width)
			max_width = trimmed_len;
		i++;
	}
	return (max_width);
}

char	**allocate_empty_grid(int width, int height)
{
	char	**result;
	int		i;
	int		j;

	result = malloc(sizeof(char *) * (height + 1));
	i = 0;
	while (i < height)
	{
		result[i] = malloc(sizeof(char) * (width + 1));
		i++;
	}
	result[i] = NULL;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			result[i][j] = '1';
			j++;
		}
		result[i][j] = '\0';
		i++;
	}
	return (result);
}

void	init_grid(t_mapinfo *mapinfo)
{
	int		i;
	char	**result;
	int		trimmed_len;
	int		k;
	char	**map;

	map = mapinfo->map;
	mapinfo->height = get_height_from_map(mapinfo->map);
	mapinfo->width = get_width_from_map(mapinfo->map);
	result = allocate_empty_grid(mapinfo->width, mapinfo->height);
	i = -1;
	while (map[++i] != NULL)
	{
		trimmed_len = len_no_space_trail(map[i]);
		k = 0;
		while (k < trimmed_len)
		{
			if (map[i][k] == ' ')
				result[i][k] = '1';
			else
				result[i][k] = map[i][k];
			k++;
		}
	}
	mapinfo->grid = result;
}
