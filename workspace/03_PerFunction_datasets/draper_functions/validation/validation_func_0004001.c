getoutputkcode(VOID_A)
{
# ifdef	DEP_PTY
	if (parentfd >= 0 && ptyoutkcode != NOCNV) return(ptyoutkcode);
# endif
	return(outputkcode);
}
