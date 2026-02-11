distributed_dim_one_array_du_semnode(Module_table *module,
                                     Array_def_use_table_semnode *src1,
                                     Array_def_use_table_semnode *src2)
{
    Array_region_list_semnode *arl1;
    Array_region_list_semnode *arl2;

    int dim = NO_SHARE;

    if (src1 == NULL || src2 == NULL) {
        return NO_SHARE;
    }

    for (arl1 = src1->region_head; arl1 != NULL; arl1 = arl1->next) {
        for (arl2 = src2->region_head; arl2 != NULL; arl2 = arl2->next) {
            int new_dim;
            new_dim = distributed_dim_array_region_semnode(module, arl1, arl2);
            if (dim == NO_SHARE) {
                dim = new_dim;
            } else if (new_dim != dim) {
                return UNKNOWN_SHARE;
            }
        }
    }

    return dim;
}
