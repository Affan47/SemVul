void LibRaw::removeExcessiveSpaces(char *string)
{
	int orig_len = strlen(string);
	int i = 0;
	int j = -1;
	bool prev_char_is_space = false;
	while (++j < orig_len && string[j] == ' ');
	while (j < orig_len)  {
		if (string[j] != ' ')  {
				string[i++] = string[j++];
				prev_char_is_space = false;
		} else if (string[j++] == ' ') {
			if (!prev_char_is_space) {
				string[i++] = ' ';
				prev_char_is_space = true;
			}
		}
	}
	if (string[i-1] == ' ')
    string[i-1] = 0;
}
