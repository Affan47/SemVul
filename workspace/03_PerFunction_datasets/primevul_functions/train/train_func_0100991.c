verify_ldftn_delegate (VerifyContext *ctx, MonoClass *delegate, ILStackDesc *value, ILStackDesc *funptr)
{
	MonoMethod *method = funptr->method;


	if ((method->flags & METHOD_ATTRIBUTE_VIRTUAL) && !(method->flags & METHOD_ATTRIBUTE_FINAL) && !(method->klass->flags & TYPE_ATTRIBUTE_SEALED) && !stack_slot_is_boxed_value (value)) {

		if (IS_FAIL_FAST_MODE (ctx) && ctx->has_this_store)
			CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("Invalid ldftn with virtual function in method with stdarg 0 at  0x%04x", ctx->ip_offset));


		if (ctx->method->flags & METHOD_ATTRIBUTE_STATIC)
			CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("Invalid ldftn with virtual function at 0x%04x", ctx->ip_offset));


		if (!stack_slot_is_this_pointer (value))
			CODE_NOT_VERIFIABLE (ctx, g_strdup_printf ("Invalid object argument, it is not the this pointer, to ldftn with virtual method at  0x%04x", ctx->ip_offset));

		ctx->code [ctx->ip_offset].flags |= IL_CODE_LDFTN_DELEGATE_NONFINAL_VIRTUAL;
	}
}
