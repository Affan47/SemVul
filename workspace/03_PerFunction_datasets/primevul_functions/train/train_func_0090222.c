md_build_ref_def_hashtable(MD_CTX* ctx)
{
    int i, j;

    if(ctx->n_ref_defs == 0)
        return 0;

    ctx->ref_def_hashtable_size = (ctx->n_ref_defs * 5) / 4;
    ctx->ref_def_hashtable = malloc(ctx->ref_def_hashtable_size * sizeof(void*));
    if(ctx->ref_def_hashtable == NULL) {
        MD_LOG("malloc() failed.");
        goto abort;
    }
    memset(ctx->ref_def_hashtable, 0, ctx->ref_def_hashtable_size * sizeof(void*));


    for(i = 0; i < ctx->n_ref_defs; i++) {
        MD_REF_DEF* def = &ctx->ref_defs[i];
        void* bucket;
        MD_REF_DEF_LIST* list;

        def->hash = md_link_label_hash(def->label, def->label_size);
        bucket = ctx->ref_def_hashtable[def->hash % ctx->ref_def_hashtable_size];

        if(bucket == NULL) {

            ctx->ref_def_hashtable[def->hash % ctx->ref_def_hashtable_size] = def;
            continue;
        }

        if(ctx->ref_defs <= (MD_REF_DEF*) bucket  &&  (MD_REF_DEF*) bucket < ctx->ref_defs + ctx->n_ref_defs) {


            MD_REF_DEF* old_def = (MD_REF_DEF*) bucket;

            if(md_link_label_cmp(def->label, def->label_size, old_def->label, old_def->label_size) == 0) {

                continue;
            }


            list = (MD_REF_DEF_LIST*) malloc(sizeof(MD_REF_DEF_LIST) + 2 * sizeof(MD_REF_DEF*));
            if(list == NULL) {
                MD_LOG("malloc() failed.");
                goto abort;
            }
            list->ref_defs[0] = old_def;
            list->ref_defs[1] = def;
            list->n_ref_defs = 2;
            list->alloc_ref_defs = 2;
            ctx->ref_def_hashtable[def->hash % ctx->ref_def_hashtable_size] = list;
            continue;
        }


        list = (MD_REF_DEF_LIST*) bucket;
        if(list->n_ref_defs >= list->alloc_ref_defs) {
            int alloc_ref_defs = list->alloc_ref_defs + list->alloc_ref_defs / 2;
            MD_REF_DEF_LIST* list_tmp = (MD_REF_DEF_LIST*) realloc(list,
                        sizeof(MD_REF_DEF_LIST) + alloc_ref_defs * sizeof(MD_REF_DEF*));
            if(list_tmp == NULL) {
                MD_LOG("realloc() failed.");
                goto abort;
            }
            list = list_tmp;
            list->alloc_ref_defs = alloc_ref_defs;
            ctx->ref_def_hashtable[def->hash % ctx->ref_def_hashtable_size] = list;
        }

        list->ref_defs[list->n_ref_defs] = def;
        list->n_ref_defs++;
    }


    for(i = 0; i < ctx->ref_def_hashtable_size; i++) {
        void* bucket = ctx->ref_def_hashtable[i];
        MD_REF_DEF_LIST* list;

        if(bucket == NULL)
            continue;
        if(ctx->ref_defs <= (MD_REF_DEF*) bucket  &&  (MD_REF_DEF*) bucket < ctx->ref_defs + ctx->n_ref_defs)
            continue;

        list = (MD_REF_DEF_LIST*) bucket;
        qsort(list->ref_defs, list->n_ref_defs, sizeof(MD_REF_DEF*), md_ref_def_cmp_for_sort);


        for(j = 1; j < list->n_ref_defs; j++) {
            if(md_ref_def_cmp(&list->ref_defs[j-1], &list->ref_defs[j]) == 0)
                list->ref_defs[j] = list->ref_defs[j-1];
        }
    }

    return 0;

abort:
    return -1;
}
