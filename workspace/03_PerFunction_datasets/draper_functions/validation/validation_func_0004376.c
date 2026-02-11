jl_show_any(jl_value_t *v)
{

    ios_t *s = jl_current_output_stream();
    if (jl_is_tuple(v)) {
        show_tuple((jl_tuple_t*)v, '(', ')', 1);
    }
    else if (jl_is_type(v)) {
        show_type(v);
    }
    else if (jl_is_func(v)) {
        show_function(v);
    }
    else if (jl_typeis(v,jl_intrinsic_type)) {
        ios_printf(s, "#<intrinsic-function %d>", *(uint32_t*)jl_bits_data(v));
    }
    else {
        jl_value_t *t = (jl_value_t*)jl_typeof(v);
        if (jl_is_struct_type(t)) {
            jl_struct_type_t *st = (jl_struct_type_t*)t;
            ios_puts(st->name->name->name, s);
            ios_putc('(', s);
            size_t i;
            size_t n = st->names->length;
            for(i=0; i < n; i++) {
                jl_show(nth_field(v, i));
                if (i < n-1)
                    ios_putc(',', s);
            }
            ios_putc(')', s);
        }
    }
}
