int gx_device_unsubclass(gx_device *dev)
{
    generic_subclass_data *psubclass_data;
    gx_device *parent, *child;
    gs_memory_struct_type_t *a_std = 0, *b_std = 0;
    int dynamic, ref_count;


    if (!dev)
        return 0;

    ref_count = dev->rc.ref_count;
    child = dev->child;
    psubclass_data = (generic_subclass_data *)dev->subclass_data;
    parent = dev->parent;
    dynamic = dev->stype_is_dynamic;


    if (psubclass_data != NULL && psubclass_data->forwarding_dev != NULL && psubclass_data->saved_compositor_method)
        psubclass_data->forwarding_dev->procs.create_compositor = psubclass_data->saved_compositor_method;


    if (dynamic) {
        a_std = (gs_memory_struct_type_t *)dev->stype;
        if (child)
            *a_std = *child->stype;
    }


    if (psubclass_data)
        gs_free_object(dev->memory->non_gc_memory, psubclass_data, "subclass memory for first-last page");


    if (child) {
        b_std = (gs_memory_struct_type_t *)dev->stype;
        rc_decrement(dev->icc_struct, "unsubclass device");
        rc_increment(child->icc_struct);
        memcpy(dev, child, child->stype->ssize);

        gs_set_object_type(child->memory, dev, b_std);

        dev->stype = b_std;


        dev->rc.ref_count = ref_count;


        if (child->child)
            child->child->parent = dev;
        child->parent->child = child->child;
    }


    if (child) {
        if (child->icc_struct)
            rc_decrement(child->icc_struct, "gx_unsubclass_device, icc_struct");
        if (child->PageList)
            rc_decrement(child->PageList, "gx_unsubclass_device, PageList");


        if (child->stype_is_dynamic) {

            child->parent = NULL;
            child->child = NULL;

            child->rc.ref_count = 0;


            b_std = (gs_memory_struct_type_t *)child->stype;
            b_std->finalize = NULL;


            gs_set_object_type(dev->memory->stable_memory, child, b_std);

            gs_free_object(dev->memory->stable_memory, child, "gx_unsubclass_device(device)");

            gs_free_const_object(dev->memory->non_gc_memory, b_std, "gs_device_unsubclass(stype)");
            child = 0;
        }
    }
    if(child)
        child->parent = dev;
    dev->parent = parent;


    if (dynamic) {
        dev->stype = a_std;
        dev->stype_is_dynamic = 1;
    } else {
        dev->stype_is_dynamic = 0;
    }

    return 0;
}
