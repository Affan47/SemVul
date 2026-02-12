void pb_release(const pb_field_t fields[], void *dest_struct)
{
    pb_field_iter_t iter;

    if (!dest_struct)
        return;

    if (!pb_field_iter_begin(&iter, fields, dest_struct))
        return;

    do
    {
        pb_release_single_field(&iter);
    } while (pb_field_iter_next(&iter));
}
