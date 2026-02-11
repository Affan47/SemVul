charstring_is_notdef_proc(const gs_memory_t *mem, const ref *pcstr)
{
    if (r_is_array(pcstr) && r_size(pcstr) == 4) {
        ref elts[4];
        long i;

        for (i = 0; i < 4; ++i)
            array_get(mem, pcstr, i, &elts[i]);
        if (r_has_type(&elts[0], t_name) &&
            r_has_type(&elts[1], t_integer) && elts[1].value.intval == 0 &&
            r_has_type(&elts[2], t_integer) && elts[2].value.intval == 0 &&
            r_has_type(&elts[3], t_name)
            ) {
            ref nref;

            name_enter_string(mem, "pop", &nref);
            if (name_eq(&elts[0], &nref)) {
                name_enter_string(mem, "setcharwidth", &nref);
                if (name_eq(&elts[3], &nref))
                    return true;
            }
        }
    }
    return false;
}
