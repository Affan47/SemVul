static void delete_Blocks(void)
{
    Blocks *a, *b = &blocks;


    while (b) {
        if (b->chunk)
            nasm_free(b->chunk);
        a = b;
        b = b->next;
        if (a != &blocks)
            nasm_free(a);
    }
    memset(&blocks, 0, sizeof(blocks));
}
