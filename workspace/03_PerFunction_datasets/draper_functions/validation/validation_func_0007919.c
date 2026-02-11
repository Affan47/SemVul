ompfbe_is_debug_barrier_module(Module_table *mp)
{
    char tmp[256];
    char *p;
    int i;

    p = debug_barrier_module_name;
    i = 0;
    for(;;) {
        tmp[i++] = *p++;
        if(*p == ',' || *p == '\0') {
            tmp[i] = '\0';
            if(!strcmp(tmp, mp->name)) return TRUE;
            if(*p == '\0') break;
            i = 0;
            p++;
        }
    }
    return FALSE;
}
