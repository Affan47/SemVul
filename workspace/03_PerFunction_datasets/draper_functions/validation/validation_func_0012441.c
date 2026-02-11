deftransaction_update(GtkWidget *widget, gpointer user_data)
{
struct deftransaction_data *data;
gboolean sensitive, bool;

	DB( g_print("(ui_transaction) update\n") );

	data = g_object_get_data(G_OBJECT(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW)), "inst_data");


	bool  = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->CM_valid));
	sensitive = bool ? FALSE : TRUE;
	gtk_widget_set_sensitive(data->CM_remind, sensitive);
	if(bool)
		gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(data->CM_remind), 0);


	sensitive = (data->ope->flags & (OF_SPLIT)) ? FALSE : TRUE;
	gtk_widget_set_sensitive(data->ST_amount, sensitive);
	gtk_widget_set_sensitive(data->PO_grp, sensitive);

}
