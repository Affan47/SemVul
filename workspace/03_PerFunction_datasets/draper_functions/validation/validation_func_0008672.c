override_email_address (EContactStore *contact_store,
                        GtkTreeIter *iter,
                        gint permutation_n,
                        gint column,
                        GValue *value,
                        ENameSelectorModel *name_selector_model)
{
	if (column == E_CONTACT_EMAIL_1) {
		EContact *contact;
		GList    *email_list;
		gchar    *email;

		contact = e_contact_store_get_contact (contact_store, iter);
		email_list = e_name_selector_model_get_contact_emails_without_used (name_selector_model, contact, TRUE);
		g_return_if_fail (g_list_length (email_list) <= permutation_n);
		email = g_strdup (g_list_nth_data (email_list, permutation_n));
		g_value_set_string (value, email);
		e_name_selector_model_free_emails_list (email_list);
	} else {
		gtk_tree_model_get_value (GTK_TREE_MODEL (contact_store), iter, column, value);
	}
}
