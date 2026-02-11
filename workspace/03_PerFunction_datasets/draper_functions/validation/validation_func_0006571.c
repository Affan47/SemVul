fil_space_is_flushed(

	fil_space_t*	space)
{
	fil_node_t*	node;

	ut_ad(mutex_own(&fil_system->mutex));

	node = UT_LIST_GET_FIRST(space->chain);

	while (node) {
		if (node->modification_counter > node->flush_counter) {

			return(FALSE);
		}

		node = UT_LIST_GET_NEXT(chain, node);
	}

	return(TRUE);
}
