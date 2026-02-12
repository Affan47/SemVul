set_context(struct compiling *c, expr_ty e, expr_context_ty ctx, const node *n)
{
    asdl_seq *s = NULL;


    const char* expr_name = NULL;


    assert(ctx != AugStore && ctx != AugLoad);

    switch (e->kind) {
        case Attribute_kind:
            if (ctx == NamedStore) {
                expr_name = "attribute";
                break;
            }

            e->v.Attribute.ctx = ctx;
            if (ctx == Store && forbidden_name(c, e->v.Attribute.attr, n, 1))
                return 0;
            break;
        case Subscript_kind:
            if (ctx == NamedStore) {
                expr_name = "subscript";
                break;
            }

            e->v.Subscript.ctx = ctx;
            break;
        case Starred_kind:
            if (ctx == NamedStore) {
                expr_name = "starred";
                break;
            }

            e->v.Starred.ctx = ctx;
            if (!set_context(c, e->v.Starred.value, ctx, n))
                return 0;
            break;
        case Name_kind:
            if (ctx == Store) {
                if (forbidden_name(c, e->v.Name.id, n, 0))
                    return 0;
            }
            e->v.Name.ctx = ctx;
            break;
        case List_kind:
            if (ctx == NamedStore) {
                expr_name = "list";
                break;
            }

            e->v.List.ctx = ctx;
            s = e->v.List.elts;
            break;
        case Tuple_kind:
            if (ctx == NamedStore) {
                expr_name = "tuple";
                break;
            }

            e->v.Tuple.ctx = ctx;
            s = e->v.Tuple.elts;
            break;
        case Lambda_kind:
            expr_name = "lambda";
            break;
        case Call_kind:
            expr_name = "function call";
            break;
        case BoolOp_kind:
        case BinOp_kind:
        case UnaryOp_kind:
            expr_name = "operator";
            break;
        case GeneratorExp_kind:
            expr_name = "generator expression";
            break;
        case Yield_kind:
        case YieldFrom_kind:
            expr_name = "yield expression";
            break;
        case Await_kind:
            expr_name = "await expression";
            break;
        case ListComp_kind:
            expr_name = "list comprehension";
            break;
        case SetComp_kind:
            expr_name = "set comprehension";
            break;
        case DictComp_kind:
            expr_name = "dict comprehension";
            break;
        case Dict_kind:
            expr_name = "dict display";
            break;
        case Set_kind:
            expr_name = "set display";
            break;
        case JoinedStr_kind:
        case FormattedValue_kind:
            expr_name = "f-string expression";
            break;
        case Constant_kind: {
            PyObject *value = e->v.Constant.value;
            if (value == Py_None || value == Py_False || value == Py_True
                    || value == Py_Ellipsis)
            {
                return ast_error(c, n, "cannot %s %R",
                                 ctx == Store ? "assign to" : "delete",
                                 value);
            }
            expr_name = "literal";
            break;
        }
        case Compare_kind:
            expr_name = "comparison";
            break;
        case IfExp_kind:
            expr_name = "conditional expression";
            break;
        case NamedExpr_kind:
            expr_name = "named expression";
            break;
        default:
            PyErr_Format(PyExc_SystemError,
                         "unexpected expression in %sassignment %d (line %d)",
                         ctx == NamedStore ? "named ": "",
                         e->kind, e->lineno);
            return 0;
    }

    if (expr_name) {
        if (ctx == NamedStore) {
            return ast_error(c, n, "cannot use named assignment with %s",
                         expr_name);
        }
        else {
            return ast_error(c, n, "cannot %s %s",
                         ctx == Store ? "assign to" : "delete",
                         expr_name);
        }
    }


    if (s) {
        Py_ssize_t i;

        for (i = 0; i < asdl_seq_LEN(s); i++) {
            if (!set_context(c, (expr_ty)asdl_seq_GET(s, i), ctx, n))
                return 0;
        }
    }
    return 1;
}
