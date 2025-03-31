/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix_parser_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:25 by joneves-          #+#    #+#             */
/*   Updated: 2025/03/31 22:32:17 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static bool	ft_valid_char(char c)
{
	//update brief
	if (c != '1' && c != '0' && c != ' ' && c != 'S' && c != 'N'
		&& c != 'E' && c != 'W' && c != 'D' && c != 'X')
		return (false);
	return (true);
}

/**
 * @brief Sets the player's position and direction on the map.
 * 
 * This function sets the player's position on the map by storing the
 * coordinates in the `player_squ_x` and `player_squ_y` variables. It also
 * determines the player's facing direction based on the character passed 
 * ('N', 'S', 'E', 'W'). The function ensures that the player is only 
 * placed once on the map.
 * 
 * @param c The character representing the player's direction ('N', 'S', 
 *          'E', or 'W').
 * @param cub The main structure holding map data.
 * @param x The x-coordinate (row) of the player on the map.
 * @param y The y-coordinate (column) of the player on the map.
 * @return true if the player's position and direction were successfully 
 *         set, false if the player was already placed on the map.
 */
static bool	ft_set_player(char c, t_cub *cub, int x, int y)
{
	if (cub->map->player_squ_x == -1)
	{
		cub->map->player_squ_x = y;
		cub->map->player_squ_y = x;
		if (c == 'S')
			cub->map->direction = SOUTH;
		if (c == 'N')
			cub->map->direction = NORTH;
		if (c == 'E')
			cub->map->direction = EAST;
		if (c == 'W')
			cub->map->direction = WEST;
	}
	else
		return (false);
	return (true);
}

static bool	ft_check_line(char *line, char *previous_line, int y, t_cub *cub)
{
	int	x;

	x = 0;
	while (line[x])
	{
		if (!ft_valid_char(line[x]))
			return (false);
		if (line[x] == 'S' || line[x] == 'N' || line[x] == 'E'
			|| line[x] == 'W')
		{
			if (!ft_set_player(line[x], cub, x, y))
				return (false);
		}
		if (line[x] == 'X')
		{
			if (!is_valid_sprite(line, previous_line, x))
				return (false);
			ft_set_sprite(cub, x, y);
		}
		if (line[x] == 'D')
		{
			if (!is_valid_door(line, previous_line, x))
				return (false);
			ft_set_door(cub, x, y);
		}
		x++;
	}
	return (true);
}

/**
 * @brief Checks if a string contains only numeric characters.
 * 
 * Verifies whether the given string consists exclusively of digits (0-9). 
 * The function iterates over each character in the string and checks if each 
 * one is a valid digit. If any non-digit character is found, the function 
 * returns false.
 * 
 * @param nbr The string to check, as a null-terminated char array.
 * @return 1 if the string is entirely numeric, 0 otherwise.
 */
int	ft_isnumeric(char *nbr)
{
	int	i;

	i = 0;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief Parses the map matrix and validates the map's structure.
 * 
 * This function iterates through each line of the map matrix, checking if 
 * the characters in each line are valid using `ft_check_line`. It also 
 * validates the wall structure and player position using `ft_valid_wall` 
 * and `ft_set_player`. If any issues are found, an error message is raised.
 * 
 * @param cub The main structure holding the map data.
 * @param matrix The map matrix to be parsed, represented as an array of strings.
 * @return void
 */
void	ft_matrix_parser(t_cub *cub, char **matrix)
{
	int		y;
	bool	first_or_last;
	char	*line;
	char	*previous_line;

	y = 0;
	previous_line = NULL;
	while (matrix[y])
	{
		first_or_last = false;
		if (y == 0 || y + 1 == cub->map->height)
			first_or_last = true;
		line = matrix[y];
		if (y > 0)
			previous_line = matrix[y - 1];
		if (!ft_check_line(line, previous_line, y, cub))
			ft_handle_error(MSG_MAP, cub);
		if (!ft_valid_wall(line, previous_line, first_or_last))
			ft_handle_error(MSG_MAP, cub);
		y++;
	}
	if (cub->map->player_squ_x == -1)
		ft_handle_error(MSG_MAP, cub);
}
