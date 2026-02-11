speech_processing_sound(struct ast_channel *chan, const char *data)
{
	int res = 0;
	struct ast_speech *speech = find_speech(chan);

	if (speech == NULL)
		return -1;

	if (speech->processing_sound != NULL) {
		ast_free(speech->processing_sound);
		speech->processing_sound = NULL;
	}

	speech->processing_sound = ast_strdup(data);

	return res;
}
