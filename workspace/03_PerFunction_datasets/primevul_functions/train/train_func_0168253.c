calc_vma_size (WinLibrary *fi)
{
    Win32ImageSectionHeader *seg;
    size_t c, segcount, size;

    size = 0;
    RETURN_IF_BAD_POINTER(-1, PE_HEADER(fi->memory)->file_header.number_of_sections);
    segcount = PE_HEADER(fi->memory)->file_header.number_of_sections;


    if (segcount == 0)
        return fi->total_size;

    RETURN_IF_BAD_PE_SECTIONS(-1, fi->memory);
    seg = PE_SECTIONS(fi->memory);
    RETURN_IF_BAD_POINTER(-1, *seg);

    for (c = 0 ; c < segcount ; c++) {
        RETURN_IF_BAD_POINTER(0, *seg);

        size = MAX(size, seg->virtual_address + seg->size_of_raw_data);

        size = MAX(size, seg->virtual_address + seg->misc.virtual_size);
        seg++;
    }

    return size;
}
