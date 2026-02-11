init_joy_config(void)
{
    int i, k;

    for (i = 0; i < 2; i++)
        for (k = 0; k < 8; k++)
            joycfg_buttons[i][k] = k;
}
