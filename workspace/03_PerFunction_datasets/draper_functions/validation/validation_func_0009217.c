addrbook_delete_book_file(AddressBookFile *book)
{
	gchar *book_path;

	if (!book->path || !book->fileName)
		return;

	book_path = g_strconcat(book->path, G_DIR_SEPARATOR_S,
				book->fileName, NULL);
	claws_unlink(book_path);
	g_free(book_path);
}
