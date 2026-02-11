optimize(unsigned long x)
{
    unsigned long   l, counter;
    ALI_TARRAY < ali_pathmap_up_pointer > *(*buffer)[];

    if ((*up_pointers)[x] == 0 || (*optimized)[x / 8] & (0x01 << (7 - (x % 8))))
        return;

    for (l = 0, counter = 0; l < height; l++)
        if ((*up_pointers)[x][l] != 0)
            counter++;

    if (counter == 0) {
        free((char *) (*up_pointers)[x]);
        (*up_pointers)[x] = 0;
        return;
    }
    (*optimized)[x / 8] |= (unsigned char) (0x01 << (7 - (x % 8)));

    buffer = (ALI_TARRAY < ali_pathmap_up_pointer > *(*)[])
        CALLOC((unsigned int) counter + 1,
               sizeof(ALI_TARRAY < ali_pathmap_up_pointer > *));
    if (buffer == 0)
        ali_fatal_error("Out of memory");

    for (l = 0, counter = 0; l < height; l++)
        if ((*up_pointers)[x][l] != 0)
            (*buffer)[counter++] = (*up_pointers)[x][l];
    (*buffer)[counter] = 0;

    free((char *) (*up_pointers)[x]);
    (*up_pointers)[x] = (ALI_TARRAY < ali_pathmap_up_pointer > **) buffer;
}
