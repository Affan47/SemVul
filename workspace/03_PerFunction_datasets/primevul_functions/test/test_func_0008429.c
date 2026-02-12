static void ok_inflater_make_huffman_tree_from_array(ok_inflater_huffman_tree *tree,
                                                     const uint8_t *code_length, int length) {
    tree->bits = 1;


    unsigned int code_length_count[MAX_CODE_LENGTH];
    int i;
    for (i = 0; i < MAX_CODE_LENGTH; i++) {
        code_length_count[i] = 0;
    }
    for (i = 0; i < length; i++) {
        code_length_count[code_length[i]]++;
    }


    unsigned int next_code[MAX_CODE_LENGTH];
    unsigned int code = 0;
    for (i = 1; i < MAX_CODE_LENGTH; i++) {
        code = (code + code_length_count[i - 1]) << 1;
        next_code[i] = code;
        if (code_length_count[i] != 0) {
            tree->bits = (unsigned int)i;
        }
    }


    const unsigned int max = 1 << tree->bits;
    memset(tree->lookup_table, 0, sizeof(tree->lookup_table[0]) * max);


    for (i = 0; i < length; i++) {
        unsigned int len = code_length[i];
        if (len != 0) {
            code = next_code[len];
            next_code[len]++;

            unsigned int value = (unsigned int)i | (len << VALUE_BITS);
            tree->lookup_table[ok_inflater_reverse_bits(code, len)] = (uint16_t)value;
        }
    }


    int next_limit = 1;
    int num_bits = 0;
    int mask = 0;
    for (i = 1; i < (int)max; i++) {
        if (i == next_limit) {
            mask = (1 << num_bits) - 1;
            num_bits++;
            next_limit <<= 1;
        }
        if (tree->lookup_table[i] == 0) {
            tree->lookup_table[i] = tree->lookup_table[i & mask];
        }
    }
}
