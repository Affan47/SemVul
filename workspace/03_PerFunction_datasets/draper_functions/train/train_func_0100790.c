mono_vcall_trampoline (mgreg_t *regs, guint8 *code, int slot, guint8 *tramp)
{
	MonoObject *this_arg;
	MonoVTable *vt;
	gpointer *vtable_slot;
	MonoMethod *m;
	gpointer addr;

	trampoline_calls ++;


	this_arg = (MonoObject *)mono_arch_get_this_arg_from_call (regs, code);
	g_assert (this_arg);

	vt = this_arg->vtable;

	if (slot >= 0) {

		vtable_slot = &(vt->vtable [slot]);


		addr = mono_aot_get_method_from_vt_slot (mono_domain_get (), vt, slot);
		if (addr && !vt->klass->valuetype) {
			if (mono_domain_owns_vtable_slot (mono_domain_get (), vtable_slot))
				*vtable_slot = addr;

			return mono_create_ftnptr (mono_domain_get (), addr);
		}


		m = mono_class_get_vtable_entry (vt->klass, slot);
	} else {

		vtable_slot = &(((gpointer*)vt) [slot]);

		m = NULL;
	}

	return common_call_trampoline (regs, code, m, vt, vtable_slot);
}
