/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jadithya <jadithya@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 17:47:37 by jadithya          #+#    #+#             */
/*   Updated: 2022/07/19 17:36:39 by jadithya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

int	ft_validfd(int fd, size_t *buffer)
{
	*buffer = BUFFER_SIZE;
	if ((fd > 0 && fd < FOPEN_MAX) || BUFFER_SIZE > 0)
		return (1);
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*hold;
	char		*buf;
	int			i;
	size_t		buffer;

	i = ft_validfd(fd, &buffer);
	while (i > 0 && ft_hasnextline(hold) == 0)
	{
		buf = (char *) ft_calloc (buffer + 1, sizeof(char));
		i = read(fd, buf, buffer) > 0;
		if (i > 0)
			hold = ft_join (hold, buf);
		free (buf);
	}
	if (!hold)
		return (NULL);
	if (i < 0 || hold[0] == '\0')
	{
		if (hold)
			free (hold);
		return (NULL);
	}
	buf = ft_splithold(hold);
	return (buf);
}
