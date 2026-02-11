AtomGet(Window win, Atom to_get, Atom type, int *size)
{
	unsigned char *retval;
	Atom type_ret;
	unsigned long bytes_after, num_ret;
	int format_ret;
	long length;
	void *data;

	retval = NULL;
	length = 0x7fffffff;
	XGetWindowProperty(
		dpy, win, to_get, 0L, length, False, type, &type_ret,
		&format_ret, &num_ret, &bytes_after, &retval);

	if ((retval) && (num_ret > 0) && (format_ret > 0))
	{
		int asize;

		asize = atom_size(format_ret);
		data = safemalloc(num_ret * asize);
		if (data)
		{
			memcpy(data, retval, num_ret * asize);
		}
		XFree(retval);
		*size = num_ret * (format_ret >> 3);
		return data;
	}

	return NULL;
}
