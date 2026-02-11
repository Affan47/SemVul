sensors_malloc_array(void *list, int *num_el, int *max_el, int el_size)
{
	void **my_list = (void **)list;

	*my_list = malloc(el_size*A_BUNCH);
	if (! *my_list)
		sensors_fatal_error(__func__, "Allocating new elements");
	*max_el = A_BUNCH;
	*num_el = 0;
}
