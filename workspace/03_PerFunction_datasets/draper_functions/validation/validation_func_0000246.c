eval_var(struct expr *expr, struct state *state) {
    struct value *v = lookup_var(expr->ident, state);
    value_ind_t vind = clone_value(v, state);
    RET_ON_ERROR;
    push_value(vind, state);
}
