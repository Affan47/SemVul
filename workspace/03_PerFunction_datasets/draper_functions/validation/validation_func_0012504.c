seed_cmp_alloc(theft *t, theft_seed seed, void *env) {
    bool *res = malloc(sizeof(*res));
    (void)env;
    (void)t;

    theft_seed r1 = theft_random(t);


    theft_seed seed_eq_lower_4_bytes = seed | 0xFFFFFFFF00000000L;
    theft_set_seed(t, seed_eq_lower_4_bytes);

    theft_seed r2 = theft_random(t);

    if (res) {
        *res = (r1 != r2);
        return res;
    } else {
        return THEFT_ERROR;
    }
}
