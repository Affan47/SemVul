make_array_range_du_pa_block_semnode(Block *bpa_block, Block *pblock)
{
    Block *bpt;

    construct_arrayinfo(pblock->inner);

    bpt = pblock->inner;
    while(bpt != NULL){
	make_array_range_du_semnode_block(bpt);

	if(bpa_block->array_info->ExposedUse == NULL){
	    bpa_block->array_info->ExposedUse = copy_array_def_use_table_semnode(bpt->array_info->ExposedUse);
	}
	else{
	    bpa_block->array_info->ExposedUse =
		union_array_def_use_table_semnode(bpa_block->module,
						  bpa_block->array_info->ExposedUse,
						  bpt->array_info->ExposedUse);
	}
        if(bpa_block->array_info->MayUse == NULL){
            bpa_block->array_info->MayUse = copy_array_def_use_table_semnode(bpt->array_info->MayUse);
        }
        else{
            bpa_block->array_info->MayUse =
                union_array_def_use_table_semnode(bpa_block->module,
                                                  bpa_block->array_info->MayUse,
                                                  bpt->array_info->MayUse);
        }
	if(bpa_block->array_info->MayMod == NULL){
            bpa_block->array_info->MayMod = copy_array_def_use_table_semnode(bpt->array_info->MayMod);
        }
        else{
	    bpa_block->array_info->MayMod =
		union_array_def_use_table_semnode(bpa_block->module,
						  bpa_block->array_info->MayMod,
						  bpt->array_info->MayMod);
        }
	bpt = bpt->next;
    }
}
