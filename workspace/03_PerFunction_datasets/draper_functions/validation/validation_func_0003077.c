xaccTransSetDateDueTS (Transaction *trans, const Timespec *ts)
{
    if (!trans || !ts) return;
    xaccTransBeginEdit(trans);
    kvp_frame_set_timespec (trans->inst.kvp_data, TRANS_DATE_DUE_KVP, *ts);
    qof_instance_set_dirty(QOF_INSTANCE(trans));
    xaccTransCommitEdit(trans);
}
