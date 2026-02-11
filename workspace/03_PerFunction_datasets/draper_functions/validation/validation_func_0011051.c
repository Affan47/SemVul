mono_security_core_clr_check_override (MonoClass *klass, MonoMethod *override, MonoMethod *base)
{
	MonoSecurityCoreCLRLevel base_level = mono_security_core_clr_method_level (base, FALSE);
	MonoSecurityCoreCLRLevel override_level = mono_security_core_clr_method_level (override, FALSE);

	if (base_level == MONO_SECURITY_CORE_CLR_CRITICAL) {
		if (override_level != MONO_SECURITY_CORE_CLR_CRITICAL) {
			set_type_load_exception_methods (
				"Override failure for %s over %s. Override MUST be [SecurityCritical].",
				override, base);
		}
	} else {

		if (override_level == MONO_SECURITY_CORE_CLR_CRITICAL) {
			set_type_load_exception_methods (
				"Override failure for %s over %s. Override must NOT be [SecurityCritical].",
				override, base);
		}
	}
}
