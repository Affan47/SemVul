ope_amount_cell_data_function (GtkTreeViewColumn *col, GtkCellRenderer *renderer, GtkTreeModel *model, GtkTreeIter *iter, gpointer user_data)
{
Transaction *ope;
gint column = GPOINTER_TO_INT(user_data);
gchar buf[G_ASCII_DTOSTR_BUF_SIZE];
gint type;
gdouble amount;
gchar *color;


	gtk_tree_model_get(model, iter, LST_DSPOPE_DATAS, &ope, -1);
	if(column == LST_DSPOPE_BALANCE)
		amount = ope->balance;
	else
		amount = ope->amount;


	if(column == LST_DSPOPE_INCOME || column == LST_DSPOPE_EXPENSE)
	{
		type = (ope->flags & OF_INCOME) ? LST_DSPOPE_INCOME : LST_DSPOPE_EXPENSE;
		if( type != column)
		{
			g_object_set(renderer, "markup", NULL, NULL);
			return;
		}
	}


	{


		mystrfmon(buf, G_ASCII_DTOSTR_BUF_SIZE-1, amount, GLOBALS->minor);
		color = get_normal_color_amount(amount);

		g_object_set(renderer,
			"foreground",  color,
			"text", buf,
			NULL);
	}


}
