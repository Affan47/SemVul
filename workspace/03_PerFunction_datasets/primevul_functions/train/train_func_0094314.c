njs_values_equal(njs_vm_t *vm, njs_value_t *val1, njs_value_t *val2)
{
    njs_int_t    ret;
    njs_bool_t   nv1, nv2;
    njs_value_t  primitive;
    njs_value_t  *hv, *lv;

again:

    nv1 = njs_is_null_or_undefined(val1);
    nv2 = njs_is_null_or_undefined(val2);


    if (nv1 || nv2) {
        return (nv1 && nv2);
    }

    if (njs_is_numeric(val1) && njs_is_numeric(val2)) {

        return (njs_number(val1) == njs_number(val2));
    }

    if (val1->type == val2->type) {

        if (njs_is_string(val1)) {
            return njs_string_eq(val1, val2);
        }

        if (njs_is_symbol(val1)) {
            return njs_symbol_eq(val1, val2);
        }

        return (njs_object(val1) == njs_object(val2));
    }


    if (val1->type > val2->type) {
        hv = val1;
        lv = val2;

    } else {
        hv = val2;
        lv = val1;
    }


    if (njs_is_object(lv)) {
        return 0;
    }


    if (njs_is_symbol(hv)) {
        return 0;
    }


    if (njs_is_string(hv)) {
        return !njs_is_symbol(lv)
            && (njs_number(lv) == njs_string_to_number(hv, 0));
    }


    ret = njs_value_to_primitive(vm, &primitive, hv, 0);
    if (ret != NJS_OK) {
        return ret;
    }

    val1 = &primitive;
    val2 = lv;

    goto again;
}
