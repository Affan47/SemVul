defaultNoticeProcessor(void *arg, const char *message)
{
	(void) arg;

	fprintf(stderr, "%s", message);
}
