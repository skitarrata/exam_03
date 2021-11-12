#include <math.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define E1 "Error: argument\n"
#define E2 "Error: operation file corrupted\n"

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int ft_check_pos(float x, float y, float cx, float cy, float h, float w)
{
	if (x < cx || x > cx + w || y < cy || y > cy + h)
		return (0);
	else if (x - cx < 1.0 || (cx + w) - x < 1.0 || y - cy < 1.0 || (cy + h) - y < 1.0)
		return (1);
	return (2);
}

int	main (int ac, char *argv[])
{
	FILE	*file;
	int		fw, fh;
	char	backg;
	char	*map;
	int		x, y;

	int		read, pos;
	char	id, color;
	float	w, h, cx, cy;

	if (ac != 2)
		return(ft_error(E1));
	if (!(fopen(argv[1], "r")) ||
		(fscanf(file, "%d %d %c\n", &fw, &fh, &backg) != 3) ||
		!(fw > 0 && fw <= 300 && fh > 0 && fh <= 300) ||
		!(map = (char *)malloc(sizeof(char) * (fw * fh))))
		return (ft_error(E2));
	memset(map, backg, fh * fw);
	while ((read = fscanf(file, "%c %f %f %f %f %c\n", &id, &cx, &cy, &w, &h)) == 6)
	{
		if (!(w > 0 && h > 0) || !(id == 'r' || id == 'R'))
			break;
		y = -1;
		while (++y < fh)
		{
			x = -1;
			while (++x < fw)
			{
				pos = ft_check_pos((float)x, (float)y, cx, cy, h, w);
				if (pos == 1 || (pos == 2 && id == 'R'))
					map[y * fw + x] = color;
			}
		}
	}
	if (read != -1)
	{
		free(map);
		return (ft_error(E2));
	}
	y = -1;
	while (++y < fh)
	{
		write(1, map + y * fw, fw);
		write(1, "\n", 1);
	}
	free(map);
	fclose(file);
	return (0);
}
