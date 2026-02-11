free_copied_array_info(Block *head)
{
    Block *bpt;

    for(bpt = head; bpt != NULL; bpt = bpt->next){
	if(bpt->copied_array_info != NULL){
	    free_all_array_def_use_table_semnode(bpt->copied_array_info->MayUse);
	    bpt->copied_array_info->MayUse = NULL;
	    free_all_array_def_use_table_semnode(bpt->copied_array_info->MayMod);
	    bpt->copied_array_info->MayMod = NULL;
	    free_all_array_def_use_table_semnode(bpt->copied_array_info->ExposedUse);
	    bpt->copied_array_info->ExposedUse = NULL;
	    free_all_array_def_use_table_semnode(bpt->copied_array_info->Kill);
	    bpt->copied_array_info->Kill = NULL;
	    free(bpt->copied_array_info);
	}
    }
}
