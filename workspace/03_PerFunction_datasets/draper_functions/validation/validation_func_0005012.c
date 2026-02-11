gf_modules_free_module(ModuleInstance *inst)
{
	void *objinterface;
	while (gf_list_count(inst->interfaces)) {
		objinterface = gf_list_get(inst->interfaces, 0);
		gf_list_rem(inst->interfaces, 0);
		inst->destroy_func(objinterface);
	}

#ifdef WIN32
	if (inst->lib_handle) FreeLibrary(inst->lib_handle);
#else
	if (inst->lib_handle) dlclose(inst->lib_handle);
#endif
        if (inst->interfaces)
          gf_list_del(inst->interfaces);
        inst->interfaces = NULL;
        if (inst->name)
          gf_free(inst->name);
        inst->name = NULL;
	gf_free(inst);
}
