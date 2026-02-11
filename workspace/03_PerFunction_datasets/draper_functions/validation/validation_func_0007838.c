cfile_getstring(cfile cf,const char *key,const char *def)
{
    int opt;

    for (opt = 0; opt < cf->n_kv; opt++) {
	if (*key == cf->kvlist[opt].key[0] &&
	    !strcmp(key, cf->kvlist[opt].key))
	  return cf->kvlist[opt].value;
    }
    return def;
}
