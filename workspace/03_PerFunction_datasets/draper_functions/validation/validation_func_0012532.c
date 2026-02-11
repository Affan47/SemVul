expect_char(char c)
{
    char buf[11];

    skip_junk(1);
    if(*pos != c) {
	sprintf(buf, "expected %c", c);
	syntax(buf, 1);
    }
    pos++;
}
