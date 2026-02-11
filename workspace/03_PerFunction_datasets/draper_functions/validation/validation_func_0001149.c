hm_dir_close(hm_dir_t *dir){
	size_t i;
	for(i = 0; i < dir->count; ++i){
		hm_file_t *file = & dir->files[i];

		hm_file_close(file);


		free( (void *) file->filename );
	}

	free(dir->files);
}
