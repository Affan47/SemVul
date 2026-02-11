sub_var_optional(sub_context_ty *scp, const char *name)
{
    table_ty        *the_end;
    table_ty        *svp;

    the_end = scp->sub_var_list + scp->sub_var_pos;
    for (svp = scp->sub_var_list; svp < the_end; ++svp)
        if (!strcmp(svp->name, name))
            break;
    assert(svp < the_end);
    if (svp < the_end)
        svp->must_be_used = 0;
}
