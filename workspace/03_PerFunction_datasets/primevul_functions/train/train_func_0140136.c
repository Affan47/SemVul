int PackLinuxElf32::canUnpack()
{
    if (checkEhdr(&ehdri)) {
        return false;
    }

    if (Elf32_Ehdr::ET_DYN==get_te16(&ehdri.e_type)) {
        PackLinuxElf32help1(fi);
    }
    if (super::canUnpack()) {
        return true;
    }
    return false;
}
