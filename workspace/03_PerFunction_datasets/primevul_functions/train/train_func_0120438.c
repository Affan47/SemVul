unres_data_del(struct unres_data *unres, uint32_t i)
{

    if (i+1 < unres->count) {

        memmove(&unres->node[i], &unres->node[i+1], (unres->count-(i+1)) * sizeof *unres->node);


    } else if (i == 0) {
        free(unres->node);
        unres->node = NULL;
    }


    --unres->count;
}
