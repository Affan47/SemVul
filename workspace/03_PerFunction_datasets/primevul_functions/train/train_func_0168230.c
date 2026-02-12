void fli_read_header(FILE *f, s_fli_header *fli_header)
{
	fli_header->filesize=fli_read_long(f);
	fli_header->magic=fli_read_short(f);
	fli_header->frames=fli_read_short(f);
	fli_header->width=fli_read_short(f);
	fli_header->height=fli_read_short(f);
	fli_header->depth=fli_read_short(f);
	fli_header->flags=fli_read_short(f);
	if (fli_header->magic == HEADER_FLI) {

		fli_header->speed=fli_read_short(f)*14;
	} else {
		if (fli_header->magic == HEADER_FLC) {

			fli_header->speed=fli_read_long(f);
		} else {
			fprintf(stderr, "error: magic number is wrong !\n");
			fli_header->magic = NO_HEADER;
		}
	}

	if (fli_header->width == 0)
	  fli_header->width = 320;

	if (fli_header->height == 0)
	  fli_header->height = 200;
}
