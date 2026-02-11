text_render_key_pressed(GtkWidget *widget, GdkEventKey *event, gpointer data)
{
    g_return_val_if_fail (widget != NULL, FALSE);
    g_return_val_if_fail (IS_TEXT_RENDER (widget), FALSE);

    TextRender *obj = TEXT_RENDER(widget);
    if (!obj->priv->dp)
        return FALSE;

    switch (event->keyval)
    {
    case GDK_Up:
        obj->priv->current_offset =
            gv_scroll_lines(obj->priv->dp, obj->priv->current_offset, -1);
        break;

    case GDK_Page_Up:
        obj->priv->current_offset =
            gv_scroll_lines(obj->priv->dp, obj->priv->current_offset,
                -1 *(obj->priv->lines_displayed-1));
        break;

    case GDK_Page_Down:
        obj->priv->current_offset =
            gv_scroll_lines(obj->priv->dp, obj->priv->current_offset,
                (obj->priv->lines_displayed-1));
        break;

    case GDK_Down:
        obj->priv->current_offset =
            gv_scroll_lines(obj->priv->dp, obj->priv->current_offset, 1);
        break;

    case GDK_Left:
        if (!obj->priv->wrapmode)
            if (obj->priv->column>0)
                obj->priv->column--;
        break;

    case GDK_Right:
        if (!obj->priv->wrapmode)
            obj->priv->column++;
        break;

    case GDK_Home:
        obj->priv->current_offset = 0;
        break;

    case GDK_End:
        obj->priv->current_offset =
            gv_align_offset_to_line_start(obj->priv->dp, gv_file_get_max_offset(obj->priv->fops)-1);
        break;

    default:
        return FALSE;
    }

    text_render_position_changed(obj);
    text_render_redraw(obj);

    return TRUE;
}
