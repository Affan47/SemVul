smartypants_cb__parens(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
	if (size >= 3) {
		uint8_t t1 = tolower(text[1]);
		uint8_t t2 = tolower(text[2]);

		if (t1 == 'c' && t2 == ')') {
			BUFPUTSL(ob, "&copy;");
			return 2;
		}

		if (t1 == 'r' && t2 == ')') {
			BUFPUTSL(ob, "&reg;");
			return 2;
		}

		if (size >= 4 && t1 == 't' && t2 == 'm' && text[3] == ')') {
			BUFPUTSL(ob, "&trade;");
			return 3;
		}
	}

	bufputc(ob, text[0]);
	return 0;
}
