/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:05:05 by aeid              #+#    #+#             */
/*   Updated: 2024/09/11 20:04:37 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minirt.h"

static bool	assign_position_light(char *line, t_elem *elem, int *status)
{
	char	**split_position;

	split_position = ft_split(line, ',');
	if (ft_split_len(split_position) != 3)
	{
		(*status)++;
		printf("%s", ERROR_LIGHT_POSITION);
		ft_free_split(split_position);
		return (true);
	}
	elem->pos.x = ft_atof(split_position[0]);
	elem->pos.y = ft_atof(split_position[1]);
	elem->pos.z = ft_atof(split_position[2]);
	ft_free_split(split_position);
	return (false);
}

static void	assign_color_light(char *line, t_elem *elem, int *status)
{
	char	**split_color;

	split_color = ft_split(line, ',');
	if (ft_split_len(split_color) != 3)
	{
		(*status)++;
		printf("%s", ERROR_LIGHT_COLOR);
		ft_free_split(split_color);
		return ;
	}
	if (validate_color_values(split_color, status, 1))
		return ;
	elem->color.r = ft_atoi(split_color[0]);
	elem->color.g = ft_atoi(split_color[1]);
	elem->color.b = ft_atoi(split_color[2]);
	ft_free_split(split_color);
	if (elem->color.r < 0 || elem->color.r > 255 || elem->color.g < 0
		|| elem->color.g > 255 || elem->color.b < 0 || elem->color.b > 255)
	{
		(*status)++;
		printf("%s", ERROR_LIGHT_COLOR);
	}
}

void	check_assign_light(char **l_split, t_elem *elem, int *status)
{
	if (ft_split_len(l_split) != 4 || check_digits(l_split))
	{
		(*status)++;
		printf("%s", ERROR_LIGHT);
		return ;
	}
	if (assign_position_light(l_split[1], elem, status))
		return ;
	elem->ratio = ft_atof(l_split[2]);
	if (elem->ratio < 0 || elem->ratio > 1 || isnan(elem->ratio))
	{
		(*status)++;
		printf("%s", ERROR_LIGHT_RATIO);
		return ;
	}
	assign_color_light(l_split[3], elem, status);
}