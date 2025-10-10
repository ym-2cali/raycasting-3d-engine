#include "inc/cub3d.h"

typedef struct s_data 
{
	void	*img;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
} t_data ;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int main(int ac, char **av)
{
	void	*mlx;
	void	*win;
	int		x = 0;
	int		y = 0;
	t_data	img;

	(void)ac;
	(void)av;
	mlx = mlx_init();
	win = mlx_new_window(mlx, 1920, 1080, "hello");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);
	while (x < 100 && y < 100)
		my_mlx_pixel_put(&img, x++, y++, 0x00FF0000);
	y = 0;
	while (x > 0  && y < 100)
		my_mlx_pixel_put(&img, x--, y++, 0x00FF0000);
	x = 0;
	while (x < 100)
		my_mlx_pixel_put(&img, x++, y, 0x00FF0000);
	y = 0;
	while (y < 100)
		my_mlx_pixel_put(&img, x, y++, 0x00FF0000);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}