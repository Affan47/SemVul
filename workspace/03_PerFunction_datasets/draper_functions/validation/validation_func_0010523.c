ExprCheckCorrectness(ExprByteCode * expr)
{
    int i;
    int stacklen = 0;
    int ternary = 0;


    for (i = 0; i < expr->len; i++) {
        ScriptToken *t = &expr->token[i];
        const struct Jim_ExprOperator *op = JimExprOperatorInfoByOpcode(t->type);

        stacklen -= op->arity;
        if (stacklen < 0) {
            break;
        }
        if (t->type == JIM_EXPROP_TERNARY || t->type == JIM_EXPROP_TERNARY_LEFT) {
            ternary++;
        }
        else if (t->type == JIM_EXPROP_COLON || t->type == JIM_EXPROP_COLON_LEFT) {
            ternary--;
        }


        stacklen++;
    }
    if (stacklen != 1 || ternary != 0) {
        return JIM_ERR;
    }
    return JIM_OK;
}
