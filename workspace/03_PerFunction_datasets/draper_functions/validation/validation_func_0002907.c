wi_array_with_data(void *data0, ...) {
	wi_array_t	*array;
	void		*data;
	va_list		ap;

	array = wi_array_init_with_capacity(wi_array_alloc(), 0);

	_wi_array_add_data(array, data0);

	va_start(ap, data0);

	while((data = va_arg(ap, void *)))
		_wi_array_add_data(array, data);

	va_end(ap);

	return wi_autorelease(array);
}
