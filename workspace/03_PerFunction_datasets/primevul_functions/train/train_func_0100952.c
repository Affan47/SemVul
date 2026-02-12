mono_image_module_basic_init (MonoReflectionModuleBuilder *moduleb)
{
	MonoDynamicImage *image = moduleb->dynamic_image;
	MonoReflectionAssemblyBuilder *ab = moduleb->assemblyb;
	if (!image) {
		MonoError error;
		int module_count;
		MonoImage **new_modules;
		MonoImage *ass;
		char *name, *fqname;


		name = mono_string_to_utf8 (ab->name);
		fqname = mono_string_to_utf8_checked (moduleb->module.fqname, &error);
		if (!mono_error_ok (&error)) {
			g_free (name);
			mono_error_raise_exception (&error);
		}
		image = create_dynamic_mono_image (ab->dynamic_assembly, name, fqname);

		moduleb->module.image = &image->image;
		moduleb->dynamic_image = image;
		register_module (mono_object_domain (moduleb), moduleb, image);


		ass = ab->dynamic_assembly->assembly.image;
		module_count = ass->module_count;
		new_modules = g_new0 (MonoImage *, module_count + 1);

		if (ass->modules)
			memcpy (new_modules, ass->modules, module_count * sizeof (MonoImage *));
		new_modules [module_count] = &image->image;
		mono_image_addref (&image->image);

		g_free (ass->modules);
		ass->modules = new_modules;
		ass->module_count ++;
	}
}
