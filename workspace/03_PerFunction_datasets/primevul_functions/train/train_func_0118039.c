fstring_find_literal_and_expr(const char **str, const char *end, int raw,
                              int recurse_lvl, PyObject **literal,
                              expr_ty *expression,
                              struct compiling *c, const node *n)
{
    int result;

    assert(*literal == NULL && *expression == NULL);


    result = fstring_find_literal(str, end, raw, literal, recurse_lvl, c, n);
    if (result < 0)
        goto error;

    assert(result == 0 || result == 1);

    if (result == 1)

        return 1;

    if (*str >= end || **str == '}')


        return 0;


    assert(**str == '{');

    if (fstring_find_expr(str, end, raw, recurse_lvl, expression, c, n) < 0)
        goto error;

    return 0;

error:
    Py_CLEAR(*literal);
    return -1;
}
