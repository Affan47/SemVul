set_cond_branch_flg( Block *block )
{
    Block *bpt;
    Boolean cond_branch_flg;

    cond_branch_flg = FALSE;

    for( bpt = block->inner; !cond_branch_flg && bpt; bpt = bpt->next ){
        if( bpt->ncfsuc > 1 ){
            cond_branch_flg = TRUE;
        }
    }

    return( cond_branch_flg );
}
