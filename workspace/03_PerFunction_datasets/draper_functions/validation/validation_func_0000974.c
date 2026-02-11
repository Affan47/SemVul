load_data_from_file (const char *file_name)
{

	unsigned char enc_header[48];
	const char *extension;

	if (strlen(file_name) <= 4) {
		fprintf(stderr, "Error: file name too short\n");
		exit(1);
	}
	extension = file_name + strlen(file_name) - 4;


	if (0 == strcmp(".xls", extension) ||
	    0 == strcmp(".XLS", extension)) {
		is_doc = 0;
		extract (file_name, enc_header);
	} else if (0 == strcmp(".doc", extension) ||
	           0 == strcmp(".DOC", extension)) {
		is_doc = 1;
		extract_doc (file_name, enc_header);
	} else {
		fprintf(stderr, "Error: file extension not recognized\n");
		exit(1);
	}


	memcpy (password_salt, enc_header, 16);
	memcpy (data + 16, enc_header + 16, 16);
	memcpy (data, enc_header + 32, 16);

	printf("Data successfully loaded from %s\n", file_name);

	printf("Password salt is "); print_hex (password_salt, 16);
	printf("Encrypted verifier is "); print_hex (data + 16, 16);
	printf("Encrypted verifier hash is "); print_hex (data, 16);
}
