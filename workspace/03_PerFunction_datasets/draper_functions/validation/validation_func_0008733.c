bof_string(const char *value)
{
	bof_t *string = bof_object();

	if (string == NULL)
		return NULL;
	string->type = BOF_TYPE_STRING;
	string->size = strlen(value) + 1;
	string->value = calloc(1, string->size);
	if (string->value == NULL) {
		bof_decref(string);
		return NULL;
	}
	strcpy(string->value, value);
	string->size += 12;
	return string;
}
