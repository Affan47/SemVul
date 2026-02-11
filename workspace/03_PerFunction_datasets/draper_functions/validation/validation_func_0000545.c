sort_pairs(gconstpointer a, gconstpointer b)
{
    const sorted_set_t *pair_a = a;
    const sorted_set_t *pair_b = b;

    if (a == NULL && b == NULL) {
        return 0;
    } else if (a == NULL) {
        return 1;
    } else if (b == NULL) {
        return -1;
    }

    if (safe_str_eq(pair_a->name, pair_a->special_name)) {
        return -1;

    } else if (safe_str_eq(pair_b->name, pair_a->special_name)) {
        return 1;
    }

    if (pair_a->score < pair_b->score) {
        return 1;
    } else if (pair_a->score > pair_b->score) {
        return -1;
    }
    return 0;
}
