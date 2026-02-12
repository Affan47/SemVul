push_local (VerifyContext *ctx, guint32 arg, int take_addr)
{
	if (arg >= ctx->num_locals) {
		ADD_VERIFY_ERROR (ctx, g_strdup_printf ("Method doesn't have local %d", arg + 1));
	} else if (check_overflow (ctx)) {

		check_unverifiable_type (ctx, ctx->locals [arg]);
		if (ctx->locals [arg]->byref && take_addr)
			CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("ByRef of ByRef at 0x%04x", ctx->ip_offset));

		set_stack_value (ctx, stack_push (ctx), ctx->locals [arg], take_addr);
	}
}
