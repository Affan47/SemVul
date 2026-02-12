int udev_util_replace_chars(char *str, const char *white)
{
	size_t i = 0;
	int replaced = 0;

	while (str[i] != '\0') {
		int len;

		if (is_whitelisted(str[i], white)) {
			i++;
			continue;
		}


		if (str[i] == '\\' && str[i+1] == 'x') {
			i += 2;
			continue;
		}


		len = utf8_encoded_valid_unichar(&str[i]);
		if (len > 1) {
			i += len;
			continue;
		}


		if (isspace(str[i]) && white != NULL && strchr(white, ' ') != NULL) {
			str[i] = ' ';
			i++;
			replaced++;
			continue;
		}


		str[i] = '_';
		i++;
		replaced++;
	}
	return replaced;
}
