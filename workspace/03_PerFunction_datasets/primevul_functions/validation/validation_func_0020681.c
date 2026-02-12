static int emit_fallback_jump(u8 **pprog)
{
	u8 *prog = *pprog;
	int err = 0;

#ifdef CONFIG_RETPOLINE


	err = emit_jump(&prog, __x86_indirect_thunk_rdx, prog);
#else
	int cnt = 0;

	EMIT2(0xFF, 0xE2);
#endif
	*pprog = prog;
	return err;
}
