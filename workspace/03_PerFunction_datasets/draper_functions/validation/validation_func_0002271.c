devhelp_plugin_init_dh(DevhelpPlugin *self)
{
#ifdef HAVE_BOOK_MANAGER
	DhBookManager *book_manager;
#else
	GNode *books;
	GList *keywords;
#endif

	if (dhbase == NULL)
		dhbase = dh_base_new();
	self->priv->dhbase = dhbase;

#ifdef HAVE_BOOK_MANAGER
	book_manager = dh_base_get_book_manager(self->priv->dhbase);
	self->priv->book_tree = dh_book_tree_new(book_manager);
	self->priv->search = dh_search_new(book_manager);
#else
	books = dh_base_get_book_tree(self->priv->dhbase);
	keywords = dh_base_get_keywords(self->priv->dhbase);
	self->priv->book_tree = dh_book_tree_new(books);
	self->priv->search = dh_search_new(keywords);
#endif

	gtk_widget_show(self->priv->search);

	g_signal_connect(self->priv->book_tree, "link-selected", G_CALLBACK(on_link_clicked), self);
	g_signal_connect(self->priv->search, "link-selected", G_CALLBACK(on_link_clicked), self);
}
