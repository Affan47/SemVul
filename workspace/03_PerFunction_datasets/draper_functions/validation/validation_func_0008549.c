gtm_sr_reg_load (GncTreeModelSplitReg *model, GncTreeModelSplitRegUpdate model_update, gint num_of_rows)
{
    GncTreeModelSplitRegPrivate *priv;
    GList *node;
    gint rows = 0;

    priv = model->priv;

    if (model_update == VIEW_HOME)
    {
        priv->tlist_start = 0;

        for (node = g_list_nth (priv->full_tlist, priv->tlist_start); node; node = node->next)
        {
            Transaction *trans = node->data;

            priv->tlist = g_list_append (priv->tlist, trans);
            rows++;

            if (rows == num_of_rows)
                break;
        }
    }

    if (model_update == VIEW_END)
    {
        priv->tlist_start = g_list_length (priv->full_tlist) - num_of_rows;

        for (node = g_list_nth (priv->full_tlist, priv->tlist_start); node; node = node->next)
        {
            Transaction *trans = node->data;

            priv->tlist = g_list_append (priv->tlist, trans);
            rows++;

            if (rows == num_of_rows)
                break;
        }
    }

    if (model_update == VIEW_GOTO)
    {
        priv->tlist_start = num_of_rows - NUM_OF_TRANS*1.5;

        for (node = g_list_nth (priv->full_tlist, priv->tlist_start); node; node = node->next)
        {
            Transaction *trans = node->data;

            priv->tlist = g_list_append (priv->tlist, trans);
            rows++;

            if (rows == (NUM_OF_TRANS*3))
                break;
        }
    }
}
