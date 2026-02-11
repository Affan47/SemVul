OctApiBt0Init(void ** b,UINT32 number_of_items,UINT32 key_size, UINT32 data_size)
{
	UINT32 i;
	OCTAPI_BT0 * bb;


	if ((key_size % 4) != 0) return(OCTAPI_BT0_KEY_SIZE_NOT_MUTLIPLE_OF_UINT32);
	if ((data_size % 4) != 0) return(OCTAPI_BT0_DATA_SIZE_NOT_MUTLIPLE_OF_UINT32);


	if (*b == NULL) return(OCTAPI_BT0_MALLOC_FAILED);

	bb = (OCTAPI_BT0 *)(*b);


	bb->root_link.node_number = 0xFFFFFFFF;
	bb->root_link.depth = 0;


	bb->number_of_items = number_of_items;
	bb->key_size = key_size / 4;
	bb->data_size = data_size / 4;


	if (number_of_items != 0)
		bb->next_free_node = 0;
	else
		bb->next_free_node = 0xFFFFFFFF;


	OctApiBt0CorrectPointers(bb);


	for(i=0;i<number_of_items;i++)
	{
		bb->node[i].next_free_node = i + 1;
	}


	bb->node[number_of_items-1].next_free_node = 0xFFFFFFFF;

	bb->invalid_value = 0xFFFFFFFF;
	bb->no_smaller_key = OCTAPI_BT0_NO_SMALLER_KEY;

	return(GENERIC_OK);
}
