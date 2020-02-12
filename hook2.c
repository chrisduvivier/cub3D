/*
**  Event: printf mouse position when mouse is moved.
*/

#include "mlx.h"
#include <stdio.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

// int             close(int keycode, t_vars *vars)
// {
//     printf("keycode: [%d]\n", keycode);
//     mlx_destroy_window(vars->mlx, vars->win);
// }

int             mouse_motion_hook(int x,int y, t_vars *vars)
{
    // printf("button: [%d]\n", button);z
    printf("x: [%d] | y: [%d]\n", x, y);
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
