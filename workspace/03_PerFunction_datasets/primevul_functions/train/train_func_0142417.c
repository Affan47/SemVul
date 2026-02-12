tiff_save_write (thandle_t handle, tdata_t buf, tsize_t size)
{
        TiffSaveContext *context = (TiffSaveContext *)handle;


        if (context->pos + size > context->used)
                context->used = context->pos + size;


        if (context->used > context->allocated) {
                context->buffer = g_realloc (context->buffer, context->pos + size);
                context->allocated = context->used;
        }


        memcpy (context->buffer + context->pos, buf, size);


        context->pos += size;

        return size;
}
