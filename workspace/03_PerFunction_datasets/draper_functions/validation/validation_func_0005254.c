String_destroy(String * string)
{
	if(string == NULL)
		return false;

	if(string->characters == NULL)
		return false;

	if(!List_destroyListAndData(string->characters, free))
		return false;

	if(string->cString != NULL)
		free(string->cString);

	string->characters = NULL;
	string->cString = NULL;

	free(string);

	return true;
}
