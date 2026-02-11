cpl_vector_get_max(const cpl_vector * v)
{
    double          max;
    cpl_size        i;


    cpl_ensure(v != NULL,   CPL_ERROR_NULL_INPUT, -1.0);

    max = v->data[0];
    for (i=1; i < v->size; i++) if (v->data[i] > max) max = v->data[i];

    return max;
}
