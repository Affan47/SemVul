my_getc(void *data)
{
    struct state *s = data;
    int c;

    c = fgetc(input);
    if (c == '.' && s->prev_char == '\n') {

	c = fgetc(input);
	return EOF;
    }
    if (c == EOF)
	my_error(data, "Unexpected EOF");
    s->prev_char = c;
    return c;
}
