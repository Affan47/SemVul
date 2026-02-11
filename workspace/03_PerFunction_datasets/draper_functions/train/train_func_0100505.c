gf_modules_close_interface(GF_BaseInterface *ifce)
{
	ModuleInstance *par;
	s32 i;
	if (!ifce) return GF_BAD_PARAM;
	par = (ModuleInstance *) ifce->HPLUG;

	if (!par || !ifce->InterfaceType) return GF_BAD_PARAM;

	i = gf_list_find(par->plugman->plug_list, par);
	if (i<0) return GF_BAD_PARAM;

	i = gf_list_find(par->interfaces, ifce);
	if (i<0) return GF_BAD_PARAM;
	gf_list_rem(par->interfaces, (u32) i);
	par->destroy_func(ifce);
	gf_modules_unload_library(par);

	return GF_OK;
}
