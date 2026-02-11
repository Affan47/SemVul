transaction_commit_load(CdlTransaction transaction, CdlLoadable loadable)
{
    CYG_REPORT_FUNCNAME("CdlLoadable::transaction_commit_load");
    CYG_REPORT_FUNCARG2XV(transaction, loadable);
    CYG_PRECONDITION_CLASSC(transaction);
    CYG_PRECONDITION_CLASSC(loadable);

    CYG_UNUSED_PARAM(CdlTransaction, transaction);
    CYG_UNUSED_PARAM(CdlLoadable, loadable);

    CYG_REPORT_RETURN();
}
