_applyn(uint32_t n)
{
    value_t f = Stack[SP-n-1];
    uint32_t saveSP = SP;
    value_t v;
    if (iscbuiltin(f)) {
        v = ((builtin_t*)ptr(f))[3](&Stack[SP-n], n);
    }
    else if (isfunction(f)) {
        v = apply_cl(n);
    }
    else if (isbuiltin(f)) {
        value_t tab = symbol_value(builtins_table_sym);
        Stack[SP-n-1] = vector_elt(tab, uintval(f));
        v = apply_cl(n);
    }
    else {
        type_error("apply", "function", f);
    }
    SP = saveSP;
    return v;
}
