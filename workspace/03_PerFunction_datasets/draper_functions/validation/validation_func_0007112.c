add_rescan_timeout(void)
{
    int	timeout = res_rescan_timeout();

    rescan_due = False;

    if (rescan_timeout_id != 0)
	XtRemoveTimeOut(rescan_timeout_id);

    if (timeout > 0)
	rescan_timeout_id =
	    XtAppAddTimeOut(app_cont, timeout * 60000L,
			    rescan_timeout_callback, NULL);
    else
	rescan_timeout_id = 0;
}
