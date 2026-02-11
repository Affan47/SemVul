ast_channel_set_connected_line(struct ast_channel *chan, const struct ast_party_connected_line *connected, const struct ast_set_party_connected_line *update)
{
	if (ast_channel_connected(chan) == connected) {

		return;
	}

	ast_channel_lock(chan);
	ast_party_connected_line_set(ast_channel_connected(chan), connected, update);
	ast_channel_unlock(chan);
}
