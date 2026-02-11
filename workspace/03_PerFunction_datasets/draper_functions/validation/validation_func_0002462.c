message_tick(t_message *x)
{
    if (glist_isvisible(x->m_glist))
    {
        t_rtext *y = glist_findrtext(x->m_glist, &x->m_text);
        sys_vgui(".x%lx.c itemconfigure %sR -width 1\n",
            glist_getcanvas(x->m_glist), rtext_gettag(y));
    }
}
