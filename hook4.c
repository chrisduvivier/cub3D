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

int             button_start_hook(int button, int x, int y, t_vars *vars)
{
    *(vars->button_start) = button;
    printf("button: [%d]\n", *(vars->button_start));
    return (0);
}


// int             button_end_hook(int button, int x, int y, t_vars *vars)
// {
//     *(vars->button_end) = button;
//     printf("END: button: [%d]\n", *(vars->button_end));
//     mlx_destroy_window(vars->mlx, vars->win);
//     return (0);
// }

int             mouse_motion_hook(int x, int y, t_vars *vars)
{
    // printf("button: [%d]\n", button);
    printf("x: [%d] | y: [%d]\n", x, y);
    return (0);
}

int             key_press_hook(int keycode, t_vars *vars)
{
    if (keycode == 53)
    {
        printf("ESC: Closing the window\n");
        mlx_destroy_window(vars->mlx, vars->win);
        return (1);
    }
    printf("Ker Press --- keycode: [%d]\n", keycode);
    return (0);
}

int             key_release_hook(int keycode, t_vars *vars)
{
    printf("Ker Release --- keycode: [%d]\n", keycode);
    return (0);
}

int             enter_window_hook(t_vars *vars)
{
    printf("Hello!\n");
    return (0);
}
int             leave_window_hook(t_vars *vars)
{
    printf("Bye!\n");
    return (0);
}

int             test(t_vars *vars)
{
    printf("Resizing window\n");
    return (0);
}

int             main(void)
{
    t_vars      vars;

    vars.mlx = mlx_init();
    vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
    mlx_hook(vars.win, 4, (1L<<2), button_start_hook, &vars);
    mlx_hook(vars.win, 6, 0L, mouse_motion_hook, &vars);
    mlx_hook(vars.win, 2, 0L, key_press_hook, &vars);
    mlx_hook(vars.win, 3, 0L, key_release_hook, &vars);
    mlx_hook(vars.win, 25, (1L<<18), test, &vars); //ResizeRequest


    mlx_hook(vars.win, 7, (1L<<4), enter_window_hook, &vars); //EnterWindowMask
    mlx_hook(vars.win, 8, (1L<<5), leave_window_hook, &vars); //LeaveWindowMask


    mlx_loop(vars.mlx);
}