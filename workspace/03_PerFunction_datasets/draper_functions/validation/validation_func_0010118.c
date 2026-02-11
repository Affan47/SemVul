e_book_get_changes_async (EBook *book,
                          const gchar *changeid,
                          EBookListAsyncCallback cb,
                          gpointer closure)
{
	GError *error;

	g_return_val_if_fail (E_IS_BOOK (book), FALSE);

	error = g_error_new (
		E_BOOK_ERROR,
		E_BOOK_ERROR_NOT_SUPPORTED,
		"Not supported");

	cb (book, error, NULL, closure);

	g_error_free (error);

	return TRUE;
}
