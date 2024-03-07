/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:30:36 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/06 16:38:04 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	key_release(int key, t_data *data)
{
	if (key == KEY_W || key == KEY_UP)
		data->key.w = false;
	else if (key == KEY_A)
		data->key.a = false;
	else if (key == KEY_S || key == KEY_DOWN)
		data->key.s = false;
	else if (key == KEY_D)
		data->key.d = false;
	else if (key == KEY_LEFT)
		data->key.l = false;
	else if (key == KEY_RIGHT)
		data->key.r = false;
	return (0);
}

int	key_press(int key, t_data *data)
{
	if (key == KEY_ESC)
		kill_program(data);
	if (key == KEY_W || key == KEY_UP)
		data->key.w = true;
	else if (key == KEY_A)
		data->key.a = true;
	else if (key == KEY_S || key == KEY_DOWN)
		data->key.s = true;
	else if (key == KEY_D)
		data->key.d = true;
	else if (key == KEY_LEFT)
		data->key.l = true;
	else if (key == KEY_RIGHT)
		data->key.r = true;
	printf("key_press %d\n", key);
	return (0);
}
