/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_validate_cubfile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:03:33 by jdaly             #+#    #+#             */
/*   Updated: 2024/03/06 21:03:43 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

char	*get_raw(char *file)
{
	int		fd;
	int		bytes;
	char	*result;

	result = (char *)malloc(sizeof(char) * MAX_MAPSIZE);
	if (!result)
		return (err_msg(NULL, "malloc error", FAILURE), NULL);
	fd = open(file, O_RDONLY);
	bytes = read(fd, result, MAX_MAPSIZE);
	if (bytes < 0)
		return (free(result), err_msg(file, "unable to read", FAILURE), NULL);
	if (bytes == 0)
		return (free(result), err_msg(file, "is empty", FAILURE), NULL);
	result[bytes] = '\0';
	return (result);
}

int	count_array_elements(char **array)
{
	int	i;

	if (!array)
		return (-1);
	i = 0;
	while (array[i])
		i++;
	return (i);
}

void	free_array(char **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}

int	check_double_nl(t_mapinfo *mapinfo)
{
	char	*map_key;
	char	*map_bgn;
	char	*result;

	map_key = mapinfo->map_bgn;
	map_bgn = ft_strnstr(mapinfo->rawdata, map_key, MAX_MAPSIZE);
	result = ft_strnstr(map_bgn, "\n\n", MAX_MAPSIZE);
	if (result != NULL)
		return (err_msg(NULL, "map has empty line", ERR_MAP));
	return (SUCCESS);
}

int	validate_cub(int argc, char **argv, t_mapinfo *m_info)
{
	if (argc != 2)
		return (err_msg("Usage", "./cub3d <path_to_map.cub>", 1));
	if (check_file(argv[1]) == FAILURE)
		return (ERR_ARG);
	printf("checked file\n");
	init_mapinfo(m_info);
	m_info->rawdata = get_raw(argv[1]);
	if (!m_info->rawdata)
		return (ERR_FILE);
	printf("mapinfo->raw:\n%s\n-------------------\n", m_info->rawdata);
	if (check_texture_info(m_info) == ERR_INFO)
		return (free_mapinfo(m_info), ERR_INFO);
	init_grid(m_info);
	if (check_size(m_info) == ERR_GRID)
		return (free_mapinfo(m_info), ERR_GRID);
	if (check_grid(m_info) == ERR_GRID)
		return (free_mapinfo(m_info), ERR_GRID);
	if (check_walls(m_info) == ERR_WALL)
		return (free_mapinfo(m_info), ERR_WALL);
	if (check_double_nl(m_info) == ERR_MAP)
		return (free_mapinfo(m_info), ERR_MAP);
	print_mapinfo(m_info);
	return (SUCCESS);
}
