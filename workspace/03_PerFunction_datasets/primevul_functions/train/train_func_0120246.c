void replace_nonprintable_char(int ifd, char *comment)
{
	int i;


	sa_fread(ifd, comment, MAX_COMMENT_LEN, HARD_SIZE, UEOF_STOP);
	comment[MAX_COMMENT_LEN - 1] = '\0';


	for (i = 0; i < strlen(comment); i++) {
		if (!isprint(comment[i]))
			comment[i] = '.';
	}
}
