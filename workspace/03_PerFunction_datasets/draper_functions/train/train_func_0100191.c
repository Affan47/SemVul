ves_icall_System_Reflection_Assembly_GetExecutingAssembly (void)
{
	MonoMethod *dest = NULL;

	mono_stack_walk_no_il (get_executing, &dest);
	g_assert (dest);
	return mono_assembly_get_object (mono_domain_get (), dest->klass->image->assembly);
}
