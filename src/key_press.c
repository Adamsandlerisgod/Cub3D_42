/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:30:36 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/08 19:49:47 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

int	kill_program(t_data *data)
{
	(void)data;
	exit(0);
	return (0);
}

int	key_release(int key, t_data *data)
{
	if (key == KEY_W || key == KEY_UP)
		data->key.w = FALSE;
	else if (key == KEY_A)
		data->key.a = FALSE;
	else if (key == KEY_S || key == KEY_DOWN)
		data->key.s = FALSE;
	else if (key == KEY_D)
		data->key.d = FALSE;
	else if (key == KEY_LEFT)
		data->key.l = FALSE;
	else if (key == KEY_RIGHT)
		data->key.r = FALSE;
	return (0);
}

int	key_press(int key, t_data *data)
{
	if (key == KEY_ESC)
		kill_program(data);
	if (key == KEY_W || key == KEY_UP)
		data->key.w = TRUE;
	else if (key == KEY_A)
		data->key.a = TRUE;
	else if (key == KEY_S || key == KEY_DOWN)
		data->key.s = TRUE;
	else if (key == KEY_D)
		data->key.d = TRUE;
	else if (key == KEY_LEFT)
		data->key.l = TRUE;
	else if (key == KEY_RIGHT)
		data->key.r = TRUE;
	return (0);
}

int	mouse_press(int click, int x, int y, t_data *data)
{
	x = y;
	y = x;
	if (click == LEFT_CLICK)
		data->key.left_click = TRUE;
	else if (click == RIGHT_CLICK)
		data->key.right_click = TRUE;
	return (0);
}

int	mouse_release(int click, int x, int y, t_data *data)
{
	x = y;
	y = x;
	if (click == LEFT_CLICK)
		data->key.left_click = FALSE;
	else if (click == RIGHT_CLICK)
		data->key.right_click = FALSE;
	return (0);
}
