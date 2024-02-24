/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ps_check_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdaly <jdaly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:45:10 by justindaly        #+#    #+#             */
/*   Updated: 2024/02/23 18:54:38 by jdaly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

static	int	is_dir(char *arg)
{
	int		fd;

	fd = open(arg, O_DIRECTORY); //O_DIRECTORY ensures it is a directory
	if (fd >= 0)
	{
		close(fd);
		return (1);
	}
	return (0);
}

static	int	is_cub_file(char *arg)
{
	size_t	len;

	len = ft_strlen(arg);
	if ((arg[len - 3] != 'c' || arg[len - 2] != 'u'
			|| arg[len - 1] != 'b' || arg[len - 4] != '.'))
		return (0);
	return (1);
}

int	check_file(char *arg)
{
	int	fd;

	if (is_dir(arg))
		return (err_msg(arg, "is a directory", FAILURE));
	fd = open(arg, O_RDONLY);
	if (fd == -1)
		return (err_msg(arg, strerror(errno), FAILURE));
	close(fd);
	if (!is_cub_file(arg)) //checks if it is a .cub file
		return (err_msg(arg, "is not a .cub file", FAILURE));
	return (SUCCESS);
}
