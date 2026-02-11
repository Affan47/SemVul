String_equalsIgnoreCase(String * string, String * string2)
{
	if(string == NULL && string == NULL)
		return true;

	if(string == NULL || string2 == NULL)
		return false;

	return List_isEqual(string->characters, string2->characters, compareCaseInsensitive);
}
