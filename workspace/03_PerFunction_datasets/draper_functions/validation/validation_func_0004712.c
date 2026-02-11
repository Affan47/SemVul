mailbox_unlock_index(struct mailbox *mailbox, struct statusdata *sdata)
{

    int r = mailbox_commit(mailbox);
    if (r) {
	syslog(LOG_ERR, "IOERROR: failed to commit mailbox %s, "
	       "probably need to reconstruct",
	       mailbox->name);
	abort();
    }

    if (mailbox->has_changed) {
	if (updatenotifier) updatenotifier(mailbox->name);
	sync_log_mailbox(mailbox->name);
	statuscache_invalidate(mailbox->name, sdata);
	mailbox->has_changed = 0;
    }
    else if (sdata) {

	statuscache_invalidate(mailbox->name, sdata);
    }

    if (mailbox->index_locktype) {
	if (lock_unlock(mailbox->index_fd))
	    syslog(LOG_ERR, "IOERROR: unlocking index of %s: %m",
		mailbox->name);
    }

    mailbox->index_locktype = 0;
}
