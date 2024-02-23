/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_validate_cubfile.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:03:33 by jdaly             #+#    #+#             */
/*   Updated: 2024/02/23 18:50:36 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

//check 1
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

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	validate_cub(int argc, char **argv, t_mapinfo *m_info)
{
	if (argc != 2)
		return (err_msg("Usage", "./cub3d <path_to_map.cub>", 1));
	if (check_file(argv[1]) == FAILURE)
		return (ERR_ARG);
	printf("checked file\n");
	init_mapinfo(m_info);
	print_mapinfo(m_info);
	printf("reading map...\n");
	m_info->rawdata = get_raw(argv[1]);
	if (!m_info->rawdata)
		return (ERR_FILE);
	printf("mapinfo->raw:\n%s\n-------------------\n", m_info->rawdata);
	if (check_texture_info(m_info) == ERR_INFO) //check 2: extract texture info, check all info is there
		return (free_mapinfo(m_info), ERR_INFO);
	init_grid(m_info); //initialize grid standardizing width
	if (check_grid(m_info) == ERR_GRID) //check map chars and player start
		return (free_mapinfo(m_info), ERR_GRID);
	if (check_walls(m_info) == ERR_WALL) //flood fill to make sure walls are closed
		return (free_mapinfo(m_info), ERR_WALL);
	print_mapinfo(m_info);
	free_mapinfo(m_info);
	return (0);
}