ast_channel_alert_write(struct ast_channel *chan)
{
	char blah = 0x7F;
	return ast_channel_alert_writable(chan) && write(chan->alertpipe[1], &blah, sizeof(blah)) != sizeof(blah);
}
