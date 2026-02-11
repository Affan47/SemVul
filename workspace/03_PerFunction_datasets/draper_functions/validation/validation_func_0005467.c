remove_contact_line(struct contact *ec)
{
	LList *accounts;

	if (!ec->list_item)
		return;

	for (accounts = ec->accounts; accounts; accounts = accounts->next) {
		eb_account *ea = accounts->data;
		if (ea->list_item)
			remove_account_line(ea);
	}

	ec->group->contacts_shown--;
	gtk_tree_store_remove(GTK_TREE_STORE(contact_list_store),
		ec->list_item);

	ec->list_item = ec->tree = ec->pix = ec->status = ec->label = NULL;

	if (ec->icon_handler != -1)
		eb_timeout_remove(ec->icon_handler);
	ec->icon_handler = -1;
}
