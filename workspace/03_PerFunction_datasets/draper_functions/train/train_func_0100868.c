ng_check_magic(int magic, char *plugname, char *type)
{
    char *h;

    h=strrchr(plugname,'/');
    if (h)
	h++;
    else
	h=plugname;

    if (magic != NG_PLUGIN_MAGIC) {
	fprintf(stderr, "ERROR: plugin magic mismatch [me=%x,%s=%x]\n",
		NG_PLUGIN_MAGIC,h,magic);
	return -1;
    }
#if 0
    if (ng_debug)
	fprintf(stderr,"plugins: %s registered by %s\n",type,plugname);
#endif
    return 0;
}
