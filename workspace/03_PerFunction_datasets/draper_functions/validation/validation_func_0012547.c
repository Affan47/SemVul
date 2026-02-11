clear()
{
    ListType().swap(d->list);


    if (d->devlist)
    {
        ftdi_list_free(&d->devlist);
        d->devlist = 0;
    }
}
