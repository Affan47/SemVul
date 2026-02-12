mono_type_get_object (MonoDomain *domain, MonoType *type)
{
	MonoType *norm_type;
	MonoReflectionType *res;
	MonoClass *klass = mono_class_from_mono_type (type);


	type = klass->byval_arg.byref == type->byref ? &klass->byval_arg : &klass->this_arg;


	if (type->type == MONO_TYPE_VOID && domain->typeof_void)
		return (MonoReflectionType*)domain->typeof_void;


	if (type == &klass->byval_arg && !klass->image->dynamic) {
		MonoVTable *vtable = mono_class_try_get_vtable (domain, klass);
		if (vtable && vtable->type)
			return vtable->type;
	}

	mono_loader_lock ();
	mono_domain_lock (domain);
	if (!domain->type_hash)
		domain->type_hash = mono_g_hash_table_new_type ((GHashFunc)mymono_metadata_type_hash,
				(GCompareFunc)mymono_metadata_type_equal, MONO_HASH_VALUE_GC);
	if ((res = mono_g_hash_table_lookup (domain->type_hash, type))) {
		mono_domain_unlock (domain);
		mono_loader_unlock ();
		return res;
	}


	norm_type = mono_type_normalize (type);
	if (norm_type != type) {
		res = mono_type_get_object (domain, norm_type);
		mono_g_hash_table_insert (domain->type_hash, type, res);
		mono_domain_unlock (domain);
		mono_loader_unlock ();
		return res;
	}


	if ((type->type == MONO_TYPE_GENERICINST) && type->data.generic_class->is_dynamic && !type->data.generic_class->container_class->wastypebuilder)
		g_assert (0);

	if (!verify_safe_for_managed_space (type)) {
		mono_domain_unlock (domain);
		mono_loader_unlock ();
		mono_raise_exception (mono_get_exception_invalid_operation ("This type cannot be propagated to managed space"));
	}

	if (mono_class_get_ref_info (klass) && !klass->wastypebuilder) {
		gboolean is_type_done = TRUE;


		if (klass->byval_arg.type == MONO_TYPE_MVAR || klass->byval_arg.type == MONO_TYPE_VAR) {
			MonoGenericParam *gparam = klass->byval_arg.data.generic_param;

			if (gparam->owner && gparam->owner->is_method) {
				MonoMethod *method = gparam->owner->owner.method;
				if (method && mono_class_get_generic_type_definition (method->klass)->wastypebuilder)
					is_type_done = FALSE;
			} else if (gparam->owner && !gparam->owner->is_method) {
				MonoClass *klass = gparam->owner->owner.klass;
				if (klass && mono_class_get_generic_type_definition (klass)->wastypebuilder)
					is_type_done = FALSE;
			}
		}


		if (is_type_done && !type->byref) {
			mono_domain_unlock (domain);
			mono_loader_unlock ();
			return mono_class_get_ref_info (klass);
		}
	}
#ifdef HAVE_SGEN_GC
	res = (MonoReflectionType *)mono_gc_alloc_pinned_obj (mono_class_vtable (domain, mono_defaults.monotype_class), mono_class_instance_size (mono_defaults.monotype_class));
#else
	res = (MonoReflectionType *)mono_object_new (domain, mono_defaults.monotype_class);
#endif
	res->type = type;
	mono_g_hash_table_insert (domain->type_hash, type, res);

	if (type->type == MONO_TYPE_VOID)
		domain->typeof_void = (MonoObject*)res;

	mono_domain_unlock (domain);
	mono_loader_unlock ();
	return res;
}
