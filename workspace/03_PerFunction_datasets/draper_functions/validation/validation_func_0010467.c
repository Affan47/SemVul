reader_init_stream(ojcErr err, Reader reader, FILE *file) {
    if (0 == file) {
	snprintf(err->msg, sizeof(err->msg) - 1, "No source file provided during initialization.");
	return;
    }
    reader_init(reader);
    reader->read_func = read_from_file;
    reader->file = file;
}
