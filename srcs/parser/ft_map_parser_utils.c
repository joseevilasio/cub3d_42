#include "../../includes/cub3d.h"

/**
 * @brief Sets the texture for a specific direction in the game map.
 * 
 * Assigns the given texture file path to the appropriate direction in the 
 * map's texture fields (north, south, west, or east). If the texture for the 
 * given direction has already been set, the function does not overwrite it.
 * 
 * @param game A pointer to the game structure (t_game) containing the map 
 *            and its texture data.
 * @param filepath The path to the texture file to be assigned.
 * @param direction The direction for which to set the texture (NORTH, SOUTH, 
 *                  WEST, or EAST).
 * @return true if the texture was successfully set, false if the direction 
 *         already has a texture assigned or if the direction is invalid.
 */
static bool	ft_set_texture(t_game *game, char *filepath, t_directions direction)
{
	if (direction == NORTH && !game->map->north_texture)
		game->map->north_texture = filepath;
	else if (direction == SOUTH && !game->map->south_texture)
		game->map->south_texture = filepath;
	else if (direction == WEST && !game->map->west_texture)
		game->map->west_texture = filepath;
	else if (direction == EAST && !game->map->east_texture)
		game->map->east_texture = filepath;
	else
		return (false);
	return (true);
}

/**
 * @brief Processes and adds a texture to the game map based on the input line.
 * 
 * Parses the provided line to extract the texture file path for a specific 
 * direction (north, south, west, or east). It ensures that the file path has 
 * a valid extension (.xpm), the file exists, and the texture for the given 
 * direction is not already set. If any condition is violated, an error is 
 * triggered and handled appropriately.
 * 
 * @param line The input line containing the texture definition.
 * @param game A pointer to the game structure (t_game) where the texture will 
 *            be stored.
 * @param identifier The identifier used to check if the line corresponds to 
 *                   the correct texture type (e.g., "NO", "SO").
 * @param direction The direction for which to assign the texture (NORTH, 
 *                  SOUTH, WEST, or EAST).
 */
void	ft_add_texture(char *line, t_game *game, char *identifier, \
	t_directions direction)
{
	char	*new_line;
	char	**tmp;
	char	*filepath;

	new_line = ft_strip(ft_strdup(line));
	tmp = ft_split(new_line, ' ');
	free(new_line);
	if (tmp[2])
		return (ft_free_vector(tmp), free(line), \
			ft_handle_error(MSG_TEXTURE, game));
	if (ft_strncmp(identifier, tmp[0], ft_strlen(tmp[0])) == 0)
	{
		filepath = ft_strip(ft_strdup(tmp[1]));
		ft_free_vector(tmp);
		if (!ft_is_ext(filepath, ".xpm"))
			return (free(filepath), ft_handle_error(MSG_TEXTURE, game)); //ext
		if (!ft_access(filepath))
			return (free(filepath), ft_handle_error(MSG_TEXTURE, game)); // file
		if (!ft_set_texture(game, filepath, direction))
			return (free(line), ft_handle_error(MSG_TEXTURE, game)); //duplicate
	}
}

/**
 * @brief Appends a line to a buffer, handling empty lines and errors.
 * 
 * Checks if the given line is empty. If the line is empty and it's the first 
 * line (start == 0), it frees both the line and the buffer, and triggers an 
 * error. Otherwise, it appends the line to the existing buffer and returns 
 * the updated buffer. If the line is empty, it returns NULL to indicate that 
 * no appending occurred.
 * 
 * @param buffer The current buffer to which the line will be appended.
 * @param line The line to append to the buffer.
 * @param start The position indicating if it's the first line (start == 0).
 * @param game A pointer to the game structure (t_game) to handle errors.
 * @return The updated buffer with the line appended, or NULL if the line is 
 *         empty.
 */
char	*ft_buffer(char *buffer, char *line, int start, t_game *game)
{
	char	*tmp;

	if (ft_isempty(line) == 1 && start == 0)
	{
		free(line);
		free(buffer);
		ft_handle_error("Map: error new line", game);
	}
	if (ft_isempty(line) == 1)
		return (NULL);
	tmp = ft_strjoin(buffer, line);
	free(buffer);
	return (tmp);
}
