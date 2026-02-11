fs_rand_copy(fs_rand_context *rand) {
    fs_rand_context *new_rand;

    if (rand == NULL) {
        return NULL;
    }

    new_rand = fs_new0(fs_rand_context, 1);
    memcpy(new_rand, rand, sizeof(fs_rand_context));

    return new_rand;
}
