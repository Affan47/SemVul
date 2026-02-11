shell_put (Camera __unused__ *camera, const char *args) {
	char arg[1024];
	unsigned int x;
	char dest_folder[MAX_FOLDER_LEN], dest_filename[MAX_FILE_LEN];

	for (x = 0; x < shell_arg_count (args); x++) {
		CHECK (shell_arg (args, x, arg));
		CHECK (shell_construct_path ("/", arg, dest_folder, dest_filename));
		CHECK (action_camera_upload_file (p, dest_folder, dest_filename));
	}

	return (GP_OK);
}
