#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int		w;
int		h;
char	bg;
char	**tab;

typedef struct	s_draw
{
	char	t;
	float	x;
	float	y;
	float	r;
	char	c;
}				t_draw;

int		err_msg(FILE *fd, int err)
{
	if (err == 2 && (err = 1))
		write(1, "ERROR\n", 6);
	else if (err == 1)
		write(1, "error argument\n", 15);
	else
	{
		for (int i = 0; i < h; i++)
		{
			write(1, tab[i], w);
			write(1, "\n", 1);
		}
	}
	if (fd)
		fclose(fd);
	return (err);
}

int		main(int ac, char **av)
{
	t_draw	el;
	FILE	*fd;
	float	sqr;
	int		res;

	fd = NULL;
	if (ac != 2)
		return (err_msg(fd, 1));
	if ((fd = fopen(av[1], "r")))
	{
		if ((res = fscanf(fd, "%d %d %c", &w, &h, &bg)) == 3)
		{
			if (w > 0 && w <= 300 && h > 0 && h <= 300)
			{
				tab = malloc(h * sizeof(char *));
				for (int i = 0; i < h; i++)
				{
					tab[i] = malloc(w * sizeof(char));
					memset(tab[i], bg, w);
				}
				while (1)
				{
					res = fscanf(fd, "\n%c %f %f %f %c", &el.t, &el.x, &el.y, &el.r, &el.c);
					if (res == -1)
						return (err_msg(fd, 0));
					else if (res != 5 || el.r <= 0 || (el.t != 'c' && el.t != 'C'))
						break ;
					for (int line = 0; line < h; line++)
					{
						for (int col = 0; col < w; col++)
						{
							sqr = sqrtf((col - el.x) * (col - el.x) + (line - el.y) * (line - el.y));
							if ( sqr <= el.r)
							{
								if (el.t == 'c' && sqr + 1 > el.r)
									tab[line][col] = el.c;
								else if (el.t == 'C')
									tab[line][col] = el.c;
							}
						}
					}
				}
			}
		}
	}
	return (err_msg(fd, 2));
}