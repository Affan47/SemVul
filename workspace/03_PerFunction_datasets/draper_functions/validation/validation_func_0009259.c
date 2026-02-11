song_select_play(void *data, Evas_Object *obj, void *event_info)
{
	int pos, ret, i;
	char *path, cmd[255], buf[PATH_MAX];
	Evas_Object *li = data;

	if(timer1) ecore_timer_del(timer1);
	Elm_Object_Item *gl_item = (Elm_Object_Item *)elm_genlist_selected_item_get(li);
	if(!gl_item) return;
	_dir *song_data = (_dir *)elm_object_item_data_get(gl_item);
	if (strcmp(song_data->path, "/Add Songs using the 'Songs' Button!") == 0) return;
	pos = song_data->type;
	if (!randomize) {
		song_index = pos;
		path = path_songs[song_index];
	}
	else {

		for (i=0; i<no_songs-1; i++) if (seq[i] == pos) break;
		song_index = i;
		path = path_songs[seq[song_index]];
	}
	if (strcmp(path, "/Add Songs using the 'Songs' Button!") == 0) return;
	ret = check_file_exists(path);
	if (!ret) {
		elm_object_item_disabled_set(song_list[song_index], EINA_TRUE);
		return;
	}

	sprintf(cmd, "loadfile \"%s\"\n", path);
	ret = write(fd, cmd, strlen(cmd));
	pos_time = 0;
	play_state = PLAYING;

	timer1 = ecore_timer_add(1.0, timer_func, NULL);

	if (view == LISTVIEW) {
		if (old_song != gl_item) elm_genlist_item_update(old_song);
		elm_genlist_item_update(gl_item);
	}
	else if(view == ALBUM_ART) show_song_info();
	else if(view == LYRICS) show_song_lyrics();
	ret = set_duration();


	snprintf(buf, sizeof(buf), "%s/pause.png", intone_dir);
	elm_icon_file_set(ic_play, buf, NULL);
	elm_object_text_set(play_cur_pos, "0:00");
	elm_slider_value_set(pos_slider, 0.0);
	old_song = gl_item;
}
