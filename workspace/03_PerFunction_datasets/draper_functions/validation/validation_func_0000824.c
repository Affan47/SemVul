exp_wait_zero(WAIT_STATUS_TYPE *status)
{
    int i;

    for (i=0;i<sizeof(WAIT_STATUS_TYPE);i++) {
	((char *)status)[i] = 0;
    }
}
