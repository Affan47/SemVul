error_EXEC_function_real(void)
{
	RELEASE_MANY(SP, EXEC.nparam);
	STACK_pop_frame(&EXEC_current);
}
