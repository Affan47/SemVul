static void iter_from_extension(pb_field_iter_t *iter, pb_extension_t *extension)
{


    const pb_field_t *field = (const pb_field_t*)extension->type->arg;
    (void)pb_field_iter_begin(iter, field, extension->dest);
    iter->pData = extension->dest;
    iter->pSize = &extension->found;

    if (PB_ATYPE(field->type) == PB_ATYPE_POINTER)
    {


        iter->pData = &extension->dest;
    }
}
