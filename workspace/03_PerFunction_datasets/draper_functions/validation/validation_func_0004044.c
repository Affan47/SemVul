clear_cache(gpointer key, gpointer val, gpointer data)
{
    ObMenu *menu = val;
    if (menu->execute)
        menu_clear_entries(menu);
}
