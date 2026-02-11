get_menu_position(vimmenu_T *menu)
{
    vimmenu_T	*node;
    int		idx = 0;

    for (node = menu->parent->children; node != menu; node = node->next)
    {
	g_return_val_if_fail(node != NULL, -1);
	++idx;
    }

    return idx;
}
