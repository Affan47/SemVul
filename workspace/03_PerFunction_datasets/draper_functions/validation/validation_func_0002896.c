show_song_info(void)
{
	char *path, *tystr, buf[255];
	int n, ret;


	if (randomize) path = path_songs[seq[song_index]];
	else path = path_songs[song_index];

	strcpy(buf, path);
	n = strlen(buf);
	buf[n-3] = 'j';
	buf[n-2] = 'p';
	buf[n-1] = 'g';
	ret = check_file_exists (buf);

	if (!ret) {
		tystr = strrchr(path, '/');
		tystr++;
		n = strlen(path) - strlen(tystr);
		strncpy(buf, path, n);
		buf[n] = '\0';
		strcat(buf, "cover.jpg");
		ret = check_file_exists (buf);
	}

	if (!ret) snprintf(buf, sizeof(buf), "%s/no-album-art.jpg", intone_dir);

   	elm_image_file_set(im, buf, NULL);

	set_song_info();

	elm_object_text_set(artist_lb, cur_artist);
	if(strlen(cur_song) > 36) {
		strncpy(buf, cur_song, 34);
		buf[34] = '.'; buf[35] = '.'; buf[36] = '\0';
		elm_object_text_set(song_lb, buf);
	}
	else elm_object_text_set(song_lb, cur_song);
}
