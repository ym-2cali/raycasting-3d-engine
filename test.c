#include "inc/cub3d.h"

// typedef struct s_data 
// {
// 	mlx_t*	*img;
// 	char	*addr;
// 	int		bpp;
// 	int		size_line;
// 	int		endian;
// } t_data ;

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->size_line + x * (data->bpp / 8));
// 	*(unsigned int*)dst = color;
// }

// int main(int ac, char **av)
// {
// 	void	*mlx;
// 	void	*win;
// 	int		x = 0;
// 	int		y = 0;
// 	t_data	img;

// 	(void)ac;
// 	(void)av;
// 	mlx = mlx_init(1920, 1080, "hello", 0);
// 	// win = mlx_new_window(mlx, 1920, 1080, "hello");
// 	img.img = mlx_new_image(mlx, 1920, 1080);
// 	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.size_line, &img.endian);
// 	while (x < 100 && y < 100)
// 		mlx_pixel_put(&img, x++, y++, 0x00FF0000);
// 	y = 0;
// 	while (x > 0  && y < 100)
// 		mlx_pixel_put(&img, x--, y++, 0x00FF0000);
// 	x = 0;
// 	while (x < 100)
// 		mlx_pixel_put(&img, x++, y, 0x00FF0000);
// 	y = 0;
// 	while (y < 100)
// 		mlx_pixel_put(&img, x, y++, 0x00FF0000);
// 	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
// 	mlx_loop(mlx);
// 	return (0);
// }

//--------------------------------
// #include <stdlib.h>
// #include <stdio.h>
// #include <string.h>
// #include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

// void    swap(int *a, int *b)
// {
//     int tmp;

//     tmp = *a;
//     *a = *b;
//     *b = tmp;
// }

// int *sorted(int *a, int size)
// {
//     int i = 0;
//     int j;
//     while (i < size)
//     {
//         j = i + 1;
//         while (j < size)
//         {
//             if (a[i] < a[j])
//                 swap(&a[i], &a[j]);
//             j++;
//         }
//         i++;
//     }
// }
// int main()
// {
//     int n;
//     scanf("%d", &n);
//     int *arr = malloc(sizeof(int) * n);
//     for (int i = 0; i < n; i++) {
//         int number;
//         scanf("%d", &number);
//         arr[i] = number;
//     }
//     int i = 0;
//     int c = 0;
//     while (i < n)
//     {
//         if (arr[i] < arr[n])
//             c += arr[i];
//         i++;
//     }
//     printf("%d\n", c);

//     return 0;
// }
int	main()//int ac, char **av
{
	printf("errno = %d\n", errno);
	return (0);
}