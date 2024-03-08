/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:02:38 by justindaly        #+#    #+#             */
/*   Updated: 2024/03/06 16:02:31 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	err_msg(char *content, char *err_msg, int exit_code)
{
	ft_putstr_fd("cub3d: Error", 2);
	if (content)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(content, 2);
	}
	if (err_msg)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(err_msg, 2);
	}
	ft_putstr_fd("\n", 2);
	return (exit_code);
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i] != NULL)
	{
		printf("[%d] %s (%zu)\n", i, array[i], ft_strlen(array[i]));
		i++;
	}
}

void	print_mapinfo(t_mapinfo *mapinfo)
{
	printf("no_path: %s\n", mapinfo->no_path);
	printf("so_path: %s\n", mapinfo->so_path);
	printf("we_path: %s\n", mapinfo->we_path);
	printf("ea_path: %s\n", mapinfo->ea_path);
	printf("f_color_str: %s\n", mapinfo->f_color_str);
	printf("c_color_str: %s\n", mapinfo->c_color_str);
	printf("f_color_int (rgb): %d\n", mapinfo->f_color_int);
	printf("c_color_int (rgb): %d\n", mapinfo->c_color_int);
	printf("height: %d\n", mapinfo->height);
	printf("width: %d\n", mapinfo->width);
	printf("p_start (xy): %d, %d\n", mapinfo->p_start_x, mapinfo->p_start_y);
	printf("p_start_o: %c\n", mapinfo->p_start_o);
	printf("str_first_line_map: %s\n", mapinfo->map_bgn);
	printf("=== map ===\n");
	print_array(mapinfo->map);
	printf("=== grid ===\n");
	print_array(mapinfo->grid);
}
