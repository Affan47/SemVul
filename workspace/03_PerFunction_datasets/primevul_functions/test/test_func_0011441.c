nv_suspend(cmdarg_T *cap)
{
    clearop(cap->oap);
    if (VIsual_active)
	end_visual_mode();
    do_cmdline_cmd((char_u *)"stop");
}
