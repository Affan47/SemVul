get_max_dlg_tag_in_layer(Hmdf_table *hmdf)
{
    Block *bpt;
    int max = 0;

    for (bpt = hmdf->block->inner; bpt != NULL; bpt = bpt->next) {
        if (block_has_dlg_tag(bpt)) {
            if (max < bpt->dlg_tag) {
                max = bpt->dlg_tag;
            }
        }
    }
    return max;
}
