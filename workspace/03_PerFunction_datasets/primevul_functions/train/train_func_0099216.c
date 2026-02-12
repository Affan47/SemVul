static int exif_process_undefined(char **result, char *value, size_t byte_count) {


	if (byte_count) {
		(*result) = estrndup(value, byte_count);
		return byte_count+1;
	}
	return 0;
}
