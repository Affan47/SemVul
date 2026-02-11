gobj_vis(t_gobj *x, struct _glist *glist, int flag)
{
    if (x->g_pd->c_wb && x->g_pd->c_wb->w_visfn && gobj_shouldvis(x, glist))
        (*x->g_pd->c_wb->w_visfn)(x, glist, flag);
}
