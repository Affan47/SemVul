size_t uc_context_size(uc_engine *uc)
{
    UC_INIT(uc);

    return sizeof(uc_context) + uc->cpu_context_size;
}
