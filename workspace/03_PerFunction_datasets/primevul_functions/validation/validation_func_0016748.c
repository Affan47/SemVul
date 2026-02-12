static void cil_reset_class(struct cil_class *class)
{
	if (class->common != NULL) {

		int num_common_perms = class->num_perms - class->perms.nprim;
		cil_symtab_map(&class->perms, __class_reset_perm_values, &num_common_perms);


		class->num_perms = class->perms.nprim;
		class->common = NULL;
	}
	class->ordered = CIL_FALSE;
}
