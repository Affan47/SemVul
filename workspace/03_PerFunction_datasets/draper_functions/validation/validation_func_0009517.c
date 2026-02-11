mono_arch_get_restore_context (MonoTrampInfo **info, gboolean aot)
{
	guint8 *start = NULL;
	guint8 *code;
	MonoJumpInfo *ji = NULL;
	GSList *unwind_ops = NULL;


	start = code = mono_global_codeman_reserve (256);

	amd64_mov_reg_reg (code, AMD64_R11, AMD64_ARG_REG1, 8);


	amd64_mov_reg_membase (code, AMD64_RAX, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, rax), 8);
	amd64_mov_reg_membase (code, AMD64_RCX, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, rcx), 8);
	amd64_mov_reg_membase (code, AMD64_RDX, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, rdx), 8);
	amd64_mov_reg_membase (code, AMD64_RBX, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, rbx), 8);
	amd64_mov_reg_membase (code, AMD64_RBP, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, rbp), 8);
	amd64_mov_reg_membase (code, AMD64_RSI, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, rsi), 8);
	amd64_mov_reg_membase (code, AMD64_RDI, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, rdi), 8);


	amd64_mov_reg_membase (code, AMD64_R12, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, r12), 8);
	amd64_mov_reg_membase (code, AMD64_R13, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, r13), 8);
	amd64_mov_reg_membase (code, AMD64_R14, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, r14), 8);
#if !defined(__native_client_codegen__)
	amd64_mov_reg_membase (code, AMD64_R15, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, r15), 8);
#endif


	amd64_mov_reg_membase (code, AMD64_R8, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, rsp), 8);
	amd64_mov_reg_membase (code, AMD64_R11, AMD64_R11,  G_STRUCT_OFFSET (MonoContext, rip), 8);
	amd64_mov_reg_reg (code, AMD64_RSP, AMD64_R8, 8);


	amd64_jump_reg (code, AMD64_R11);

	nacl_global_codeman_validate(&start, 256, &code);

	mono_arch_flush_icache (start, code - start);

	if (info)
		*info = mono_tramp_info_create ("restore_context", start, code - start, ji, unwind_ops);

	return start;
}
