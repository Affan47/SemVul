Dataset_Sequence_destroy(Dataset_Sequence *seq){
    if(seq->cache_seq)
        Sequence_destroy(seq->cache_seq);
    FastaDB_Key_destroy(seq->key);
    g_free(seq->id);
    if(seq->def)
        g_free(seq->def);
    g_free(seq);
    return;
    }
