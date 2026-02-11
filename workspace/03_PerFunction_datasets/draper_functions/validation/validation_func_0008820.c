screen_hide_desktop_popup(void)
{
    if (desktop_popup_timer) g_source_remove(desktop_popup_timer);
    desktop_popup_timer = 0;
    pager_popup_hide(desktop_popup);
    desktop_popup_perm = FALSE;
}
