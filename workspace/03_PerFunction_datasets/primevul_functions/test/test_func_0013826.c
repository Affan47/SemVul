ex_packloadall(exarg_T *eap)
{
    if (!did_source_packages || eap->forceit)
    {


	add_pack_start_dirs();
	load_start_packages();
    }
}
