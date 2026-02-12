void fli_write_header(FILE *f, s_fli_header *fli_header)
{
	fli_header->filesize=ftell(f);
	fseek(f, 0, SEEK_SET);
	fli_write_long(f, fli_header->filesize);
	fli_write_short(f, fli_header->magic);
	fli_write_short(f, fli_header->frames);
	fli_write_short(f, fli_header->width);
	fli_write_short(f, fli_header->height);
	fli_write_short(f, fli_header->depth);
	fli_write_short(f, fli_header->flags);
	if (fli_header->magic == HEADER_FLI) {

		fli_write_short(f, fli_header->speed / 14);
	} else {
		if (fli_header->magic == HEADER_FLC) {

			fli_write_long(f, fli_header->speed);
			fseek(f, 80, SEEK_SET);
			fli_write_long(f, fli_header->oframe1);
			fli_write_long(f, fli_header->oframe2);
		} else {
			fprintf(stderr, "error: magic number in header is wrong !\n");
		}
	}
}
