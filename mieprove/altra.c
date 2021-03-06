#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define E1 "Error: argument\n"
#define E2 "Error: Operation file corrupted\n"

int ft_strlen(char *str)
{
	int	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

int ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int ft_check(float x, float y, float cx, float cy, float width, float height)
{
	if (x < cx || x > cx + width || y < cy || y > cy + height)
		return (0);
	else if (x - cx < 1.0 || (cx + width) - x < 1.0 || y - cy < 1.0 || (cy + height) - y < 1.0)
		return (1);
	return (2);
}

int main(int argc, char *argv[])
{
	FILE *f;
	int x, y, read;
	char *map;
	char id, color, ch;
	float cx, cy, width, height;
	int w, h, pos;

	if (argc != 2)
		return (ft_error(E1));
	if (!(f = fopen(argv[1], "r")) ||
		(fscanf(f, "%d %d %c\n", &w, &h, &ch)) != 3 ||
		!(w > 0 && w <= 300 && h > 0 && h <= 300) ||
		!(map = (char *)malloc(sizeof(char) * (w * h))))
		return (ft_error(E2));
	memset(map, ch, w * h);
	while ((read = fscanf(f, "%c %f %f %f %f %c\n", &id, &cx, &cy, &width, &height, &color)) == 6)
	{
		if (!(width > 0 && height > 0) || !(id == 'R' || id == 'r'))
			break;
		y = -1;
		while (++y < h)
		{
			x = -1;
			while (++x < w)
			{
				pos = ft_check((float)x, (float)y, cx, cy, width, height);
				if (pos == 1 || (pos == 2 && id == 'R'))
					map[y * w + x] = color;
			}
		}
	}
	if (read != -1)
	{
		free(map);
		return (ft_error(E2));
	}
	y = -1;
	while (++y < h)
	{
		write(1, map + y * w, w);
		write(1, "\n", 1);
	}
	free(map);
	fclose(f);
	return (0);
}