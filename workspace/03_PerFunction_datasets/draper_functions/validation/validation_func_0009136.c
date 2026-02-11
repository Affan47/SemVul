scapegoat_remove(scapegoat* goat, Object* key, const Comparable_vtable *key_method, BOOLEAN destroy_data){
	Object *data = NULL;
	BOOLEAN success = FALSE;
	btree *tr = btree_remove(goat->root, key, key_method, &data, destroy_data, &success);
	if(success){
		goat->size--;
		goat->root = tr;
		if(goat->size < goat->a*goat->max_size){
			goat->root = btree_balance(goat->root);
			goat->max_size = goat->size;
		}

	}
	return data;
}
