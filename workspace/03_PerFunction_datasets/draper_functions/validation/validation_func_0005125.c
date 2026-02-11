mono_assembly_release_gc_roots (MonoAssembly *assembly)
{
	if (assembly == NULL || assembly == REFERENCE_MISSING)
		return;

	if (assembly->dynamic) {
		int i;
		MonoDynamicImage *dynimg = (MonoDynamicImage *)assembly->image;
		for (i = 0; i < dynimg->image.module_count; ++i)
			mono_dynamic_image_release_gc_roots ((MonoDynamicImage *)dynimg->image.modules [i]);
		mono_dynamic_image_release_gc_roots (dynimg);
	}
}
