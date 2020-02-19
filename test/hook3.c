/*
**  Event: a mouse is pressed, it will print the angle at which it moved over the window to the terminal.
*/

#include "mlx.h"
#include <stdio.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
    int         *x1;
    int         *y1;
    int         *x2;
    int         *y2;
}               t_vars;

// int             close(int keycode, t_vars *vars)
// {
//     printf("keycode: [%d]\n", keycode);
//     mlx_destroy_window(vars->mlx, vars->win);
// }

int             mouse_motion_hook(int x,int y, t_vars *vars)
{
    // printf("button: [%d]\n", button);
    vars->x1 = &x;
    vars->y1 = &y;
    printf("x: [%d] | y: [%d]\n", *vars->x1, *vars->y1);
    mlx_destroy_window(vars->mlx, vars->win);
    return (0);
}

int             main(void)
{
    t_vars      vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    mlx_hook(vars.win, 6, 0L, mouse_motion_hook, &vars);
    mlx_loop(vars.mlx);
} 