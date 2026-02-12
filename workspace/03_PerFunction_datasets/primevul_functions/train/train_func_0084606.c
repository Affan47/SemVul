static inline void tb_remove_from_jmp_list(TranslationBlock *orig, int n_orig)
{
    uintptr_t ptr, ptr_locked;
    TranslationBlock *dest;
    TranslationBlock *tb;
    uintptr_t *pprev;
    int n;


    ptr = atomic_or_fetch(&orig->jmp_dest[n_orig], 1);
    dest = (TranslationBlock *)(ptr & ~1);
    if (dest == NULL) {
        return;
    }

    ptr_locked = orig->jmp_dest[n_orig];
    if (ptr_locked != ptr) {


        g_assert(ptr_locked == 1 && dest->cflags & CF_INVALID);
        return;
    }


    pprev = &dest->jmp_list_head;
    TB_FOR_EACH_JMP(dest, tb, n) {
        if (tb == orig && n == n_orig) {
            *pprev = tb->jmp_list_next[n];

            return;
        }
        pprev = &tb->jmp_list_next[n];
    }
    g_assert_not_reached();
}
