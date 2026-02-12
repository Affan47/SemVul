static void clear_smacro_table(struct hash_table *smt, enum clear_what what)
{
    struct hash_iterator it;
    const struct hash_node *np;
    bool empty = true;


    hash_for_each(smt, it, np) {
        SMacro *tmp;
        SMacro *s = np->data;
        SMacro **head = (SMacro **)&np->data;

        list_for_each_safe(s, tmp, s) {
            if (what & ((enum clear_what)s->alias + 1)) {
                *head = s->next;
                free_smacro(s);
            } else {
                empty = false;
            }
        }
    }


    if (empty)
        hash_free_all(smt, true);
}
