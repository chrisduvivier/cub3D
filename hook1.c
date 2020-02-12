/*
**  Event: a key is pressed, it will print the key code in the terminal.
*/

#include "mlx.h"
#include <stdio.h>

typedef struct  s_vars {
    void        *mlx;
    void        *win;
}               t_vars;

int             close(int keycode, t_vars *vars)
{
    printf("keycode: [%d]\n", keycode);
    mlx_destroy_window(vars->mlx, vars->win);
}

int             main(void)
{
    t_vars      vars;
    int         done;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    mlx_key_hook(vars.win, close, &vars);
    mlx_loop(vars.mlx);
} 