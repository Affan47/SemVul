deleteNextDir()
{
    Q_Q(CopyJob);
    if ( m_mode == CopyJob::Move && !dirsToRemove.isEmpty() )
    {
        state = STATE_DELETING_DIRS;
        m_bURLDirty = true;

        KUrl::List::Iterator it = --dirsToRemove.end();
        SimpleJob *job = KIO::rmdir( *it );
        Scheduler::setJobPriority(job, 1);
        dirsToRemove.erase(it);
        q->addSubjob( job );
    }
    else
    {

        state = STATE_SETTING_DIR_ATTRIBUTES;
        m_directoriesCopiedIterator = m_directoriesCopied.constBegin();
        setNextDirAttribute();
    }
}
