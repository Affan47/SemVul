compiler_arguments(struct compiler *c, arguments_ty args)
{
    int i;
    int n = asdl_seq_LEN(args->args);

    for (i = 0; i < n; i++) {
        expr_ty arg = (expr_ty)asdl_seq_GET(args->args, i);
        if (arg->kind == Tuple_kind) {
            PyObject *id = PyString_FromFormat(".%d", i);
            if (id == NULL) {
                return 0;
            }
            if (!compiler_nameop(c, id, Load)) {
                Py_DECREF(id);
                return 0;
            }
            Py_DECREF(id);
            VISIT(c, expr, arg);
        }
    }
    return 1;
}
