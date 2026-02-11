mono_class_setup_parent (MonoClass *klass, MonoClass *parent)
{
	gboolean system_namespace;
	gboolean is_corlib = mono_is_corlib_image (klass->image);

	system_namespace = !strcmp (klass->name_space, "System") && is_corlib;


	if (system_namespace && !strcmp (klass->name, "Object")) {
		klass->parent = NULL;
		klass->instance_size = sizeof (MonoObject);
		return;
	}
	if (!strcmp (klass->name, "<Module>")) {
		klass->parent = NULL;
		klass->instance_size = 0;
		return;
	}

	if (!MONO_CLASS_IS_INTERFACE (klass)) {

#ifndef DISABLE_COM
		if (MONO_CLASS_IS_IMPORT (klass)) {
			init_com_from_comimport (klass);
			if (parent == mono_defaults.object_class)
				parent = mono_class_get_com_object_class ();
		}
#endif
		if (!parent) {

			parent = mono_defaults.object_class;
			mono_class_set_failure (klass, MONO_EXCEPTION_TYPE_LOAD, NULL);
		}

		klass->parent = parent;

		if (parent->generic_class && !parent->name) {


			return;
		}

#ifndef DISABLE_REMOTING
		klass->marshalbyref = parent->marshalbyref;
		klass->contextbound  = parent->contextbound;
#endif

		klass->delegate  = parent->delegate;

		if (MONO_CLASS_IS_IMPORT (klass) || mono_class_is_com_object (parent))
			mono_class_set_is_com_object (klass);

		if (system_namespace) {
#ifndef DISABLE_REMOTING
			if (klass->name [0] == 'M' && !strcmp (klass->name, "MarshalByRefObject"))
				klass->marshalbyref = 1;

			if (klass->name [0] == 'C' && !strcmp (klass->name, "ContextBoundObject"))
				klass->contextbound  = 1;
#endif
			if (klass->name [0] == 'D' && !strcmp (klass->name, "Delegate"))
				klass->delegate  = 1;
		}

		if (klass->parent->enumtype || (mono_is_corlib_image (klass->parent->image) && (strcmp (klass->parent->name, "ValueType") == 0) &&
						(strcmp (klass->parent->name_space, "System") == 0)))
			klass->valuetype = 1;
		if (mono_is_corlib_image (klass->parent->image) && ((strcmp (klass->parent->name, "Enum") == 0) && (strcmp (klass->parent->name_space, "System") == 0))) {
			klass->valuetype = klass->enumtype = 1;
		}

	} else {

#ifndef DISABLE_COM
		if (MONO_CLASS_IS_IMPORT (klass))
			init_com_from_comimport (klass);
#endif
		klass->parent = NULL;
	}

}
