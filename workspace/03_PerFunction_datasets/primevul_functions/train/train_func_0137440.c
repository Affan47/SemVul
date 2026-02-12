static int getfname(void *v, const char **fnamep)
{
    deliver_data_t *d = (deliver_data_t *)v;
    *fnamep = NULL;
    if (d->stage)
        *fnamep = append_stagefname(d->stage);

    return 0;
}
