is_deterministic(struct jmt *jmt) {
    list_for_each(s, jmt->start) {
        array_for_each(i, s->trans) {
            struct trans *t = state_trans(s, i);
            for (ind_t j = i+1; j < s->trans.used; j++) {
                struct trans *u = state_trans(s, j);
                if (t->lens == u->lens)
                    return false;
            }
        }
    }
    return true;
}
