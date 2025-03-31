/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_load_map_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joneves- <joneves-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:55:47 by joneves-          #+#    #+#             */
/*   Updated: 2025/03/31 22:04:36 by joneves-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/**
 * @brief Initializes the map structure within the game configuration.
 * 
 * Allocates memory for the map structure (t_map) and sets all its fields to 
 * default values. If memory allocation fails, the function handles the error 
 * appropriately. This initialization ensures the map is ready for parsing and 
 * further processing.
 * 
 * @param game A pointer to the game structure (t_game) where the map structure 
 *            will be initialized.
 */
static void	ft_init_map(t_cub *cub)
{
	cub->map = (t_map *) malloc(sizeof(t_map));
	if (!cub->map)
		ft_handle_error("Malloc: t_map", cub);
	cub->map->matrix = NULL;
	cub->map->matrix_tmp = NULL;
	cub->map->north_texture = NULL;
	cub->map->south_texture = NULL;
	cub->map->west_texture = NULL;
	cub->map->east_texture = NULL;
	cub->map->floor_rgb = NULL;
	cub->map->ceiling_rgb = NULL;
	cub->map->player_squ_x = -1;
	cub->map->player_squ_y = -1;
	cub->map->direction = -1;
	cub->map->sprite = NULL;
	cub->map->sprite_count = 0;
	cub->map->sprite_increment = 0;
	cub->map->door = NULL;
	cub->map->door_count = 0;
	cub->map->door_increment = 0;
}

/**
 * @brief Checks if a file is accessible for reading.
 * 
 * Attempts to open the specified file in read-only mode to determine whether 
 * it is accessible. If the file can be opened successfully, it is considered 
 * accessible.
 * 
 * @param filepath The path to the file to check, as a null-terminated string.
 * @return true if the file is accessible for reading, false otherwise.
 */
bool	ft_access(char *filepath)
{
	int	fd;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		return (false);
	close(fd);
	return (true);
}

/**
 * @brief Checks if a filename has a specific file extension.
 * 
 * Verifies whether the given filename ends with the specified file extension. 
 * The comparison is case-sensitive and ensures the extension matches exactly 
 * at the end of the filename.
 * 
 * @param filename The name of the file to check, as a null-terminated string.
 * @param ext The expected file extension, as a null-terminated string.
 * @return true if the filename ends with the specified extension, 
 *         false otherwise.
 */
bool	ft_is_ext(char *filename, char *ext)
{
	char	*file_ext;

	file_ext = ft_strnstr(filename, ext, ft_strlen(filename));
	if (!file_ext || ft_strlen(file_ext) != ft_strlen(ext))
	{
		return (false);
	}
	return (true);
}


void	ft_load_map(char *const filepath, t_cub *cub)
{
	int	i;

	i = 0;
	cub->fd = -1;
	cub->filepath = ft_strip(ft_strdup(filepath), 0);
	if (!ft_is_ext(cub->filepath, ".cub"))
		ft_handle_error("Map: File extension", cub);
	cub->fd = open(cub->filepath, O_RDONLY);
	if (cub->fd == -1)
		ft_handle_error(NULL, cub);
	ft_init_map(cub);
	ft_map_parser(cub->fd, cub, i);
	cub->map->sprite = malloc(sizeof(t_sprite) * cub->map->sprite_count);
	if (!cub->map->sprite)
		ft_handle_error("Map: cub->map->sprite", cub);
	cub->map->door = malloc(sizeof(t_sprite) * cub->map->door_count);
	if (!cub->map->door)
		ft_handle_error("Map: cub->map->door", cub);
	ft_matrix_parser(cub, cub->map->matrix);
	cub->map->ceiling_hex = ft_arraytohex(cub->map->ceiling_rgb);
	cub->map->floor_hex = ft_arraytohex(cub->map->floor_rgb);
	close(cub->fd);
	cub->fd = -1;
}
