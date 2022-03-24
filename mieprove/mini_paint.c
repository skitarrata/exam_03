#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define E1 "Error: argument\n"
#define E2 "Error: Operation file corrupted\n"

int	ft_strlen(char *str)
{
	int i = 0;
	while(str[i])
		i++;
	return (i);
}

int ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int ft_check(float x, float y, float cx, float cy, float r)
{
	float dis = sqrtf(powf(x - cx, 2.) + powf(y - cy, 2.0));
	if (dis <= r)
	{
		if ((r - dis) < 1.0)
			return (0);
		return (1);
	}
	return (2);
}

int main(int argc, char *argv[])
{
	FILE *f;
	int read, pos, x, y;
	char *map;
	char id, color, ch;
	int w, h;
	float cx, cy, r;

	if (argc != 2)
		return (ft_error(E1));
	if (!(f = fopen(argv[1], "r")) ||
		(fscanf(f, "%d %d %c\n", &w,&h,&ch)) != 3 ||
		!(w > 0 && w <= 300 && h > 0 && h <= 300) ||
		!(map = (char *)malloc(sizeof(char) * (w * h))))
		return (ft_error(E2));
	memset(map, ch, w * h);
	while((read = fscanf(f, "%c %f %f %f %c\n", &id,&cx,&cy,&r,&color)) == 5)
	{
		if (!(r > 0) || !(id == 'C' || id == 'c'))
			break;
		y = -1;
		while(++y < h)
		{
			x = -1;
			while(++x < w)
			{
				pos = ft_check((float)x, (float)y, cx, cy, r);
				if (pos == 0 || (pos == 1 && id == 'C'))
					map[y * w + x] = color;
			}
		}
	}
	if (read != EOF)
	{
		free(map);
		return (ft_error(E2));
	}
	y = -1;
	while(++y < h)
	{
		write(1, map + y * w, w);
		write(1, "\n", 1);
	}
	free(map);
	fclose(f);
	return (0);
}