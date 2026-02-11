MemoryTell(struct _cms_io_handler* iohandler)
{
    FILEMEM* ResData = (FILEMEM*) iohandler ->stream;

    if (ResData == NULL) return 0;
    return ResData -> Pointer;
}
