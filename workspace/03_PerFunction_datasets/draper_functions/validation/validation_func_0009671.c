lex_close(void)
{
    lex_ty          *old;

    trace(("lex_close()\n{\n"));
    assert(root);
    old = root;
    input_delete(root->l_file);
    root = old->l_chain;
    if (!root && errcnt)
    {
        sub_context_ty *scp;

        scp = sub_context_new();
        sub_var_set_string(scp, "File_Name", old->filename.logical);
        sub_var_set_long(scp, "Number", errcnt);
        sub_var_optional(scp, "Number");
        fatal_intl(scp, i18n("$filename: found $number fatal errors"));

    }
    lex_filename_destructor(&old->filename);
    lex_filename_list_destructor(&old->pending_include_list);
    free(old);
    trace(("}\n"));
}
