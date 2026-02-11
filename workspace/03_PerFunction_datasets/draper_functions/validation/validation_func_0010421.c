bof_object_set(bof_t *object, const char *keyname, bof_t *value)
{
	bof_t *key;
	int r;

	if (object->type != BOF_TYPE_OBJECT)
		return -EINVAL;
	r = bof_entry_grow(object);
	if (r)
		return r;
	key = bof_string(keyname);
	if (key == NULL)
		return -ENOMEM;
	object->array[object->array_size++] = key;
	object->array[object->array_size++] = value;
	object->size += value->size;
	object->size += key->size;
	bof_incref(value);
	return 0;
}
