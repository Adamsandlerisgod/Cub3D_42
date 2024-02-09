/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justindaly <justindaly@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:03:33 by jdaly             #+#    #+#             */
/*   Updated: 2024/02/09 17:02:59 by justindaly       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

//check 1
char	*get_raw(char *file)
{
	int 	fd;
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
    return *(unsigned char *)s1 - *(unsigned char *)s2;
}

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

int	get_texture_info(t_mapinfo *mapinfo, char *line)
{
	char **texture_data;

	texture_data = ft_split(line, ' ');
	if (count_array_elements(texture_data) != 2)
	{
		free_array(texture_data);
		return(err_msg(line, "invalid texture line", ERR_INFO));
	}
	if (!is_valid_texture_type(texture_data[0]))
	{
		free_array(texture_data);
		return(err_msg(line, "invalid texture type", ERR_INFO));
	}
	(void)mapinfo;
	free_array(texture_data);
	return (0);
}

int	check_texture_info(t_mapinfo *m_info)
{
	char	**lines;
	int		i;

	lines = ft_split(m_info->rawdata, '\n');
	i = 0;
	while (lines[i])
	{
		//check texture data
		if (get_texture_info(m_info, lines[i]) == ERR_INFO)
			return (free_array(lines), ERR_INFO);
		i++;
		//break if all textures (NO, SO, EA, WE, C, F) found
	}
	// check if there is more data after texture info
		//set first line of map
	//create 2D MAP ARRAY
	free_array(lines);
	return (0);
}

int	validate_map(int argc, char **argv, t_mapinfo *m_info)
{
	if (argc != 2)
		return (err_msg("Usage", "./cub3d <path_to_map.cub>", 1));
	if (check_file(argv[1]) == FAILURE)
		return (ERR_ARG);
	printf("checked file\n");
	init_mapinfo(m_info);
	printf("reading map...\n");
	m_info->rawdata = get_raw(argv[1]);
	if (!m_info->rawdata)
		return (ERR_FILE);
	printf("mapinfo->raw: %s\n-------------------\n", m_info->rawdata);
	//check 2: extract texture info, check all info is there
	check_texture_info(m_info);
	return (0);
}