check_mbox() {
	struct mbox_struct * mb;

	mb = mbox;
	x11_set.status = MAIL_NONE;
	while ( mb ) {
		if ( mb->mail == MAIL_NEW )
			x11_set.status = MAIL_NEW;
		else if ( (mb->mail == MAIL_OLD) && (x11_set.status != MAIL_NEW) )
			x11_set.status = MAIL_OLD;
		if ( mb->flags & FLAG_ARRIVED ) {
			pthread_mutex_lock(&mb->mutex);
			mb->flags &= ~FLAG_ARRIVED;
			pthread_mutex_unlock(&mb->mutex);
			execute_on_new();
		}
		mb = mb->next;
	}
	if ( saved_status != x11_set.status ) {
#ifdef DEBUG
	printf("asmail: check_mbox: Determined mail status as %s (was %s)\n",
			x11_set.status == MAIL_NEW ? "NEW" :
			x11_set.status == MAIL_OLD ? "OLD" : "NONE",
			saved_status == MAIL_NEW ? "NEW" :
			saved_status == MAIL_OLD ? "OLD" : "NONE");
#endif
		setup_pixmap();
		saved_status = x11_set.status;
		if ( Current && Current->next && Current->next != Current )
			need_animation = 1;
		else
			need_animation = 0;
		return 1;
	}
	return 0;
}
