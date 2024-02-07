/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:03:33 by jdaly             #+#    #+#             */
/*   Updated: 2024/02/07 18:44:04 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

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
	return (0);
}