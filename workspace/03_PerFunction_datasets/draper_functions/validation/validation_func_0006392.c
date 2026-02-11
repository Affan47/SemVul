Term_xtra(int n, int v)
{

	if (!Term->xtra_hook) return (-1);


	return ((*Term->xtra_hook)(n, v));
}
