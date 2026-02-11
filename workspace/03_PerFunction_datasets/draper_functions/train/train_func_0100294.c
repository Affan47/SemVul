garray_redraw(t_garray *x)
{
    if (glist_isvisible(x->x_glist))
        sys_queuegui(&x->x_gobj, x->x_glist, garray_doredraw);


    else
    {
      if (x->x_listviewing)
        sys_vgui("pdtk_array_listview_fillpage %s\n",
                 x->x_realname->s_name);
    }

}
