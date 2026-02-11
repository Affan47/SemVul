popup_autosize (GnomeCanvasItem *item,
                int max_width,
                gpointer user_data)
{
    PopBox *box = user_data;

    if (!box || !box->autosize)
        return max_width;

    return gnc_item_list_autosize (GNC_ITEM_LIST (item)) + 20;
}
