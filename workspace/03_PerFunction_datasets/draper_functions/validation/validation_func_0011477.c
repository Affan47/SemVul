validate_ref(astnode *n, void *arg, astnode **next)
{
    int i;
    symbol_ident_list list;
    symtab_entry *enum_def;
    int ret = 1;
    if (is_field_ref(n)) {
        return 1;
    }
    symtab_entry * e = symtab_lookup(n->ident);
    if (e == NULL) {

        symtab_list_type(ENUM_SYMBOL, &list);
        for (i=0; i<list.size; i++) {
            enum_def = symtab_lookup(list.idents[i]);
            symtab_push(enum_def->symtab);
            e = symtab_lookup(n->ident);
            symtab_pop();
            if (e != NULL) {

                astnode *scope = astnode_create_scope(
                    astnode_create_identifier(enum_def->id, n->loc),
                    astnode_clone(n, n->loc), n->loc);
                astnode_replace(n, scope);
                astnode_finalize(n);
                *next = scope;
                ret = 0;
                break;
            }
        }
        symtab_list_finalize(&list);
        if (e == NULL) {
            strtok(n->ident, "#");


            warn(n->loc, "`%s' undeclared; assuming external label", n->ident);
            e = symtab_enter(n->ident, LABEL_SYMBOL, NULL, EXTRN_FLAG);
        }
    }
    if (e)
        e->ref_count++;
    return ret;
}
