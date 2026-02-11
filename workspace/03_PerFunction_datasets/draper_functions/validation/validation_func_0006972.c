dist_info_entry_kind( Dist_info *info )
{
    if( info->dep_ope ){
	if( info->dep_ope->next ){
	    info->dep_no = -1;
	}else{
	    info->dep_no = info->dep_ope->entry;
	    info->kind = info->dep_ope->kind;
	}
    }
}
