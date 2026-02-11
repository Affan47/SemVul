read_config(const char *file)
{
	parser_t *parser;
	const struct config_keyword *k;
	unsigned i;
	char *token[2];

	for (i = 0; i < KWS_WITH_DEFAULTS; i++)
		keywords[i].handler(keywords[i].def, keywords[i].var);

	parser = config_open(file);
	while (config_read(parser, token, 2, 2, "# \t", PARSE_NORMAL)) {
		for (k = keywords, i = 0; i < ARRAY_SIZE(keywords); k++, i++) {
			if (strcasecmp(token[0], k->keyword) == 0) {
				if (!k->handler(token[1], k->var)) {
					bb_error_msg("can't parse line %u in %s",
							parser->lineno, file);

					k->handler(k->def, k->var);
				}
				break;
			}
		}
	}
	config_close(parser);

	server_config.start_ip = ntohl(server_config.start_ip);
	server_config.end_ip = ntohl(server_config.end_ip);
}
