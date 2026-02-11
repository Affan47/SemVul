hash_lookup(HASH * Hash, const char *key, const int do_sort)
{
    HASH_ITEM *Item = NULL;


    if (do_sort && !Hash->sorted) {
	qsort(Hash->Items, Hash->nItems, sizeof(HASH_ITEM), hash_sort_item);
	Hash->sorted = 1;
    }


    if (key == NULL)
	return NULL;


    if (Hash->sorted) {
	Item = bsearch(key, Hash->Items, Hash->nItems, sizeof(HASH_ITEM), hash_lookup_item);
    }


    if (Item == NULL) {
	int i;
	for (i = 0; i < Hash->nItems; i++) {
	    if (strcmp(key, Hash->Items[i].key) == 0) {
		Item = &(Hash->Items[i]);
		break;
	    }
	}
    }

    return Item;

}
