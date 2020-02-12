/*
**  Event: printf mouse position when mouse is moved.
*/

#include "mlx.h"
#include <stdio.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
    int         *button_start;
    int         *button_end;
}               t_vars;

// int             close(int keycode, t_vars *vars)
// {
//     printf("keycode: [%d]\n", keycode);
//     mlx_destroy_window(vars->mlx, vars->win);
// }

int             button_start_hook(int button, t_vars *vars)
{
    *(vars->button_start) = button;
    printf("button: [%d]\n", *(vars->button_start));
    return (0);
}


int             button_end_hook(int button, t_vars *vars)
{
    *(vars->button_end) = button;
    printf("END: button: [%d]\n", *(vars->button_end));
    mlx_destroy_window(vars->mlx, vars->win);
    return (0);
}

int             main(void)
{
    t_vars      vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    mlx_hook(vars.win, 4, (1L<<2), button_start_hook, &vars);
    mlx_hook(vars.win, 5, (1L<<3), button_end_hook, &vars);
    mlx_loop(vars.mlx);
}