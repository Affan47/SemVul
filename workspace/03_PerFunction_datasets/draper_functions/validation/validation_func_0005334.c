deftransaction_get(GtkWidget *widget, gpointer user_data)
{
struct deftransaction_data *data;
Transaction *entry;
gchar *txt;
gdouble value;
gint active;

	DB( g_print("(ui_transaction) get\n") );

	data = g_object_get_data(G_OBJECT(gtk_widget_get_ancestor(widget, GTK_TYPE_WINDOW)), "inst_data");

	entry = data->ope;

	DB( g_print(" -> ope = %p\n", entry) );


	entry->date = gtk_dateentry_get_date(GTK_DATE_ENTRY(data->PO_date));


	if(	entry->wording )
	{
		g_free(entry->wording);
		entry->wording = NULL;
	}
	txt = (gchar *)gtk_entry_get_text(GTK_ENTRY(data->ST_word));

	if (txt && *txt)
	{
		entry->wording = g_strdup(txt);
	}

	entry->paymode    = gtk_combo_box_get_active(GTK_COMBO_BOX(data->NU_mode));
	if( entry->paymode != PAYMODE_INTXFER )
	{

		entry->kxferacc = 0;
	}

	value = gtk_spin_button_get_value(GTK_SPIN_BUTTON(data->ST_amount));
	entry->amount = value;


	if(	entry->info )
	{
		g_free(entry->info);
		entry->info = NULL;
	}
	txt = (gchar *)gtk_entry_get_text(GTK_ENTRY(data->ST_info));

	if (txt && *txt)
	{
		entry->info = g_strdup(txt);
	}

	entry->kcat     = ui_cat_comboboxentry_get_key_add_new(GTK_COMBO_BOX(data->PO_grp));
	entry->kpay     = ui_pay_comboboxentry_get_key_add_new(GTK_COMBO_BOX(data->PO_pay));
	entry->kacc     = ui_acc_comboboxentry_get_key(GTK_COMBO_BOX(data->PO_acc));
	entry->kxferacc = ui_acc_comboboxentry_get_key(GTK_COMBO_BOX(data->PO_accto));


	txt = (gchar *)gtk_entry_get_text(GTK_ENTRY(data->ST_tags));
	DB( g_print(" -> tags: '%s'\n", txt) );
	transaction_tags_parse(entry, txt);


	entry->flags &= (OF_SPLIT);

	if(	data->type == TRANSACTION_EDIT_ADD || data->type == TRANSACTION_EDIT_INHERIT)
	entry->flags |= OF_ADDED;

	if(	data->type == TRANSACTION_EDIT_MODIFY)
	entry->flags |= OF_CHANGED;

	active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->CM_valid));
	if(active == 1) entry->flags |= OF_VALID;

	active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->CM_remind));
	if(active == 1) entry->flags |= OF_REMIND;

	active = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(data->CM_cheque));
	if(active == 1) entry->flags |= OF_CHEQ2;


	active = entry->amount > 0 ? TRUE : FALSE;
	if(active == TRUE) entry->flags |= OF_INCOME;

}
