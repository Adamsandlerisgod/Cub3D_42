/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whendrik <whendrik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 16:36:36 by whendrik          #+#    #+#             */
/*   Updated: 2024/02/22 14:20:33 by whendrik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast.h"

static void set_direction(t_data *data)
{
  if (data->mapinfo.p_start_o == 'N')
  {
    data->dir.x = 0;
    data->dir.y = 1;
  }
  else if (data->mapinfo.p_start_o == 'S')
  {
    data->dir.x = 0;
    data->dir.y = -1;
  }
  else if (data->mapinfo.p_start_o == 'W')
  {
    data->dir.x = 1;
    data->dir.y = 0;
  }
  else if (data->mapinfo.p_start_o == 'E')
  {
    data->dir.x = -1;
    data->dir.y = 0;
  }
}

int draw_ray(t_data *data)
{
  //x and y start position
  // double posX = t_mapinfo->p_start_x;
  // double posY = t_mapinfo->p_start_y;
  double posX = 1;
  double posY = 1;
  set_direction(data)
  double dirX = -1, dirY = 0; //initial direction vector
  // double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
}