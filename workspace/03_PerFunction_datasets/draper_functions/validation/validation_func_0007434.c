win_reshape(junk)
int	UNUSED(junk);
{
	int save_errno = errno;

	ResizePending = YES;
#ifdef UNIX
	resetsighandler(SIGWINCH, win_reshape);
	if (InSlowRead) {

		InSlowRead = NO;
		redisplay();
		InSlowRead = YES;
	}
#else
	redisplay();
#endif
	errno = save_errno;
	return SIGRESVALUE;
}
