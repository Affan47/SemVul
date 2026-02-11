play_message_to_chans(struct ast_channel *left, struct ast_channel *right, int which, const char *msg, const char *audiofile)
{

	if (which <= 0 && play_message_on_chan(left, right, msg, audiofile)) {
		return -1;
	}


	if (which >= 0 && play_message_on_chan(right, left, msg, audiofile)) {
		return -1;
	}

	return 0;
}
