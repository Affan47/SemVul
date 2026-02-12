static bool validate_bcl(IDEState *s)
{

    if (s->atapi_dma || atapi_byte_count_limit(s)) {
        return true;
    }


    ide_abort_command(s);
    return false;
}
