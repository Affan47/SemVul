Comparison_destroy(Comparison *comparison){
    g_assert(comparison);
    if(--comparison->ref_count)
        return;
    Comparison_Param_destroy(comparison->param);
    Sequence_destroy(comparison->query);
    Sequence_destroy(comparison->target);
    if(comparison->dna_hspset)
        HSPset_destroy(comparison->dna_hspset);
    if(comparison->protein_hspset)
        HSPset_destroy(comparison->protein_hspset);
    if(comparison->codon_hspset)
        HSPset_destroy(comparison->codon_hspset);
    g_free(comparison);
    return;
    }
