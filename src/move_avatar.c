/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_avatar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 18:06:20 by whendrik          #+#    #+#             */
/*   Updated: 2024/03/07 18:33:44 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

void static	move(t_data *data, double angle)
{
	t_coor_db	dir;

	dir.x = -1 * cos(angle);
	dir.y = -1 * sin(angle);
	if (data->map[(int)(data->avatar_pos.y + dir.y * SPEED)]
		[(int)(data->avatar_pos.x + dir.x * SPEED)] == '0')
	{
		data->avatar_pos.x += dir.x * SPEED / 2;
		data->avatar_pos.y += dir.y * SPEED / 2;
	}
	else if (data->map[(int)(data->avatar_pos.y)]
		[(int)(data->avatar_pos.x + dir.x * SPEED)] == '0')
		data->avatar_pos.x += dir.x * SPEED / 2;
	else if (data->map[(int)(data->avatar_pos.y + dir.y * SPEED)]
		[(int)(data->avatar_pos.x)] == '0')
		data->avatar_pos.y += dir.y * SPEED / 2;
}

void	move_avatar(t_data *data)
{
	if (data->key.w)
		move(data, data->facing_angle);
	if (data->key.a)
		move(data, data->facing_angle - PI / 2);
	if (data->key.s)
		move(data, data->facing_angle + PI);
	if (data->key.d)
		move(data, data->facing_angle + PI / 2);
	if (data->key.r || data->key.right_click)
		data->facing_angle += 0.02;
	if (data->key.l || data->key.left_click)
		data->facing_angle -= 0.02;
	if (data->facing_angle >= 2 * PI)
		data->facing_angle -= 2 * PI;
	else if (data->facing_angle <= 0)
		data->facing_angle += 2 * PI;
}
