refreshStatus()
{
    status.type = Status::Idle;
    status.nonPersistent.clear();
    status.persistent.clear();

    persistStatus(QModelIndex());
}
