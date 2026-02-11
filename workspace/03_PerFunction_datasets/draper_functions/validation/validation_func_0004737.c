is_64bit_pcrel_reloc (unsigned int reloc_type)
{
  switch (elf_header.e_machine)
    {
    case EM_AARCH64:
      return reloc_type == 260;
    case EM_ALPHA:
      return reloc_type == 11;
    case EM_IA_64:
      return reloc_type == 0x4f;
    case EM_PARISC:
      return reloc_type == 72;
    case EM_PPC64:
      return reloc_type == 44;
    case EM_SPARC32PLUS:
    case EM_SPARCV9:
    case EM_SPARC:
      return reloc_type == 46;
    case EM_X86_64:
    case EM_L1OM:
    case EM_K1OM:
      return reloc_type == 24;
    case EM_S390_OLD:
    case EM_S390:
      return reloc_type == 23;
    case EM_TILEGX:
      return reloc_type == 5;
    default:
      return FALSE;
    }
}
