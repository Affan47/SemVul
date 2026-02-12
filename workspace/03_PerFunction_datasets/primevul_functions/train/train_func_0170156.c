static bool imap_parser_read_text(struct imap_parser *parser,
				  const unsigned char *data, size_t data_size)
{
	size_t i;


	for (i = parser->cur_pos; i < data_size; i++) {
		if (is_linebreak(data[i])) {
			imap_parser_save_arg(parser, data, i);
			break;
		}
	}
	parser->cur_pos = i;
	return parser->cur_type == ARG_PARSE_NONE;
}
