vm_class_setup_object(struct vm_class *vmc)
{
	vmc->object = vm_object_alloc(vm_java_lang_Class);
	if (!vmc->object) {
		throw_oom_error();
		return -1;
	}

	field_set_object(vmc->object, vm_java_lang_Class_vmdata,
			 (struct vm_object *)vmc);
	return 0;
}
