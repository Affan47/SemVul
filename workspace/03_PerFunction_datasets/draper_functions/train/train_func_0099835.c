which_tooltip_cb (GtkWidget  *widget, gint x, gint y, gboolean keyboard_mode, GtkTooltip *tooltip, gpointer user_data)
{
    gchar *text = "";

    GncCombott *combott = GNC_COMBOTT (user_data);
    GncCombottPrivate *priv = GNC_COMBOTT_GET_PRIVATE (combott);

    if(!priv->active == 0)
    {
        gtk_tree_model_get( priv->model, &priv->active_iter, priv->tip_col, &text, -1 );
        if(g_strcmp0(text, "") && (text != NULL))
        {
            gchar *label = "";
            gtk_tooltip_set_text (tooltip, text);
            g_free(text);
            return TRUE;
        }
        else
        {
            g_free(text);
            return FALSE;
        }
    }
    return FALSE;
}
