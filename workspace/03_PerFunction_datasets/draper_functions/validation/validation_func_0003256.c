slayer_http_request_header_parse( slayer_http_request_parse_t *parse) {
	enum PARSE_REQUEST_STATE state;
	char *p = NULL;
	state = parse->header_state;
	for (p = parse->buffer_marker; p < (parse->buffer + parse->buffer_size);p++) {
		switch (state) {
		case PARSE_HEADER_START:
			switch (*p) {
			case '\r':
				state = PARSE_HEADER_START_LF;
				break;
			case '\n':
				state = PARSE_HEADER_DONE;
				goto 	HEADER_SECTION_END;
				break;
			default:
				if (check_header(*p)) {

					state = PARSE_HEADER_NAME;
				} else {
					return -1;
				}
			}
			break;
		case PARSE_HEADER_START_LF:
			if (*p == '\n') {
				state = PARSE_HEADER_DONE;
				goto HEADER_SECTION_END;
			}
			return -1;
			break;
		case PARSE_HEADER_NAME:
			if ( check_header(*p) ) {
				break;
			} else {
				switch (*p) {
				case ':':
					state = PARSE_HEADER_SPACE_BEFORE_VALUE;
					break;
				case '\r':
					state = PARSE_HEADER_DONE_LF;
					break;
				case '\n':
					state = PARSE_HEADER_START;
					goto HEADER_END;
					break;
				default:

					return -1;
				}
			}
			break;
		case PARSE_HEADER_SPACE_BEFORE_VALUE:
			switch (*p) {
			case ' ':
				break;
			case '\r':
				state = PARSE_HEADER_DONE_LF;
				break;
			case '\n':
				state = PARSE_HEADER_START;
				goto HEADER_END;
			}
			break;
		case PARSE_HEADER_VALUE:
			switch (*p) {
			case ' ':
				state = PARSE_HEADER_SPACE_AFTER_VALUE;
				break;
			case '\r':
				state = PARSE_HEADER_DONE_LF;
				break;
			case '\n':
				state = PARSE_HEADER_START;
				goto HEADER_END;
			default:
				break;
			}
			break;
		case PARSE_HEADER_SPACE_AFTER_VALUE:
			switch (*p) {
			case ' ':
				state = PARSE_HEADER_SPACE_AFTER_VALUE;
				break;
			case '\r':
				state = PARSE_HEADER_DONE_LF;
				break;
			case '\n':
				state = PARSE_HEADER_START;
				goto HEADER_END;
			default:
				state = PARSE_HEADER_VALUE;
				break;
			}
			break;
		case PARSE_HEADER_DONE_LF:
			if (*p == '\n') {
				state = PARSE_HEADER_START;
				goto HEADER_END;
			}
			return -1;
			break;
		case PARSE_HEADER_DONE:

			break;
		default:
			break;
		}

	}
HEADER_END:
	parse->buffer_marker = p +1;
	parse->header_state = state;
	return 1;
HEADER_SECTION_END:
	parse->buffer_marker = p +1;
	parse->header_state = PARSE_HEADER_DONE;
	return 0;
}
