struct SWF_ACTIONPUSHPARAM * peek()
{
#ifdef DEBUG
	printf("*peek*\n");
#endif
#ifdef DEBUGSTACK
	if( Stack == NULL ) push(newVar("// *** peek(): INTERNAL STACK ERROR FOUND ***"));
#else
	if( Stack == NULL ) SWF_error("Stack blown!! - peek");
#endif
	return Stack->val;
}
