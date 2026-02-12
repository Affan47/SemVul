int epo_finish_copydevice(gx_device *dev, const gx_device *from_dev)
{


    dev->child = NULL;
    dev->parent = NULL;
    dev->subclass_data = NULL;

    return (from_dev->memory ? gs_note_error(gs_error_rangecheck) : 0);
}
