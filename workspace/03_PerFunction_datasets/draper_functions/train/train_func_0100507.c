kcm_remove_event(krb5_context context,
		 kcm_event *event)
{
    krb5_error_code ret;
    kcm_event **e;
    int found = 0;

    log_event(event, "removing");

    HEIMDAL_MUTEX_lock(&events_mutex);
    for (e = &events_head; *e != NULL; e = &(*e)->next) {
	if (event == *e) {
	    *e = event->next;
	    found++;
	    break;
	}
    }

    if (!found) {
	ret = KRB5_CC_NOTFOUND;
	goto out;
    }

    ret = kcm_remove_event_internal(context, &event);

out:
    HEIMDAL_MUTEX_unlock(&events_mutex);

    return ret;
}
