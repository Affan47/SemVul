check_nonsense_hmdf_table_for_hmdf(Hmdf_table *hmdf)
{
    Hmdf_table *hpt1;
    Hmdf_table *hpt2;

    for (hpt1 = hmdf->parent->children; hpt1 != NULL; hpt1 = hpt1->brothers) {
        for (hpt2 = hpt1; hpt2 != NULL; hpt2 = hpt2->next) {
            if (hpt2->clustering == NULL) {
                fprintf(stderr, "Warning!! Hmdf_table has no Clustering Info!!\n");
            }
            if (hpt2->pc_num * hpt2->pe_num != hmdf->parent->pe_num
                || hpt2->pc_num < 1
                || hpt2->pe_num < 1) {
                fprintf(stderr, "Nonsense Hmdf_table!!\n");
                abort();
            }
        }
    }
}
