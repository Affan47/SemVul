add_sums_to_file(file_t* file, char* dir_path, file_set *files_to_add)
{
	FILE* fd;
	unsigned i;
	int ch;


	int print_banner = (opt.fmt == FMT_SFV);

	file->size = 0;
	if (rsh_file_stat(file) == 0) {
		if (print_banner && file->size > 0) print_banner = 0;
	}


	if ( !(fd = fopen(file->path, "r+") )) {
		log_file_error(file->path);
		return -1;
	}
	rhash_data.upd_fd = fd;

	if (file->size > 0) {

		if (fseek(fd, -1, SEEK_END) != 0) {
			log_file_error(file->path);
			return -1;
		}
		ch = fgetc(fd);


		if (fseek(fd, 0, SEEK_END) != 0) {
			log_file_error(file->path);
			return -1;
		}


		if (ch != '\n' && ch != '\r') {

			fprintf(fd, "\n");
		}
	}


	for (i = 0; i < files_to_add->size; i++, rhash_data.processed++)
	{
		file_t file;
		char *print_path = file_set_get(files_to_add, i)->filepath;
		file.wpath = 0;
		file.mode = 0;

		if (dir_path[0] != '.' || dir_path[1] != 0) {

			file.path = make_path(dir_path, print_path);
		} else {
			file.path = rsh_strdup(print_path);
		}

		if (opt.fmt == FMT_SFV) {
			if (print_banner) {
				print_sfv_banner(fd);
				print_banner = 0;
			}
		}
		rsh_file_stat(&file);


		calculate_and_print_sums(fd, &file, print_path);

		rsh_file_cleanup(&file);

		if (rhash_data.interrupted) {
			fclose(fd);
			return 0;
		}
	}
	fclose(fd);
	log_msg(_("Updated: %s\n"), file->path);
	return 0;
}
