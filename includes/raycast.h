/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: justindaly <justindaly@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:48:37 by whendrik          #+#    #+#             */
/*   Updated: 2024/02/23 14:19:23 by justindaly       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H
# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

# define MAX_MAPSIZE 5000

# define X_EVENT_KEY_PRESS	2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_KEY_EXIT	17
# define KEY_ESC     53
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_UP  	126
# define KEY_DOWN	125
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define KEY_W		13
# define KEY_M		46
# define PI	3.14159265358979

# define SUCCESS 0
# define FAILURE 1
# define TRUE 1
# define FALSE 0

# define ERR_ARG 255
# define ERR_FILE 254
# define ERR_INFO 253
# define ERR_GRID 252
# define ERR_WALL 251
# define ERR_MAP 250

typedef struct s_mapinfo
{
	char	*rawdata;
	char	**map;
	char	**grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*f_color_str;
	char	*c_color_str;
	int		f_color_int;
	int		c_color_int;
	int		p_start_x;
	int		p_start_y;
	char	p_start_o;
	//flood
	//closed
	char	*map_bgn;
}	t_mapinfo;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}		t_img;


typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	int		win_width;
	int		win_height;

}		t_mlx;

typedef struct s_coor
{
	float	x;
	float	y;
}		t_coor;

typedef struct s_data
{
	t_mlx		mlx;
	t_img		img;
	t_coor		avatar_pos;
	t_mapinfo	mapinfo;
	char		**map;
}		t_data;

/*Error*/
int		err_msg(char *content, char *err_msg, int exit_code);
void	print_mapinfo(t_mapinfo *mapinfo);

/*Validate CUB*/
void	free_array(char **array);

/*Init Map Info*/
void	free_mapinfo(t_mapinfo	*info);

/*Parsing*/
void	init_mapinfo(t_mapinfo *info);
int		check_file(char *arg);
int		validate_cub(int argc, char **argv, t_mapinfo *m_info);
void	init_grid(t_mapinfo *mapinfo);
int		check_grid(t_mapinfo *mapinfo);


/*Initialization*/
void	init_data(t_data *data, char **map);

/*Draw Functions*/
void	draw_grid(t_img *img, int width, int height);
// void	draw_grid_horizontal(t_img *img, int height);
// void	draw_grid_vertical(t_img *img, int width);
void	draw_avatar(t_data *data);
int		draw_map(t_data	*data);

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

#endif