ConvertMemoryPageAttributes (
  IN  PHYSICAL_ADDRESS                  BaseAddress,
  IN  UINT64                            Length,
  IN  UINT64                            Attributes
  )
{
  UINT64                            *PageEntry;
  PAGE_ATTRIBUTE                    PageAttribute;
  RETURN_STATUS                     Status;
  EFI_PHYSICAL_ADDRESS              MaximumAddress;

  if (Length == 0 ||
      (BaseAddress & (SIZE_4KB - 1)) != 0 ||
      (Length & (SIZE_4KB - 1)) != 0) {

    ASSERT (Length > 0);
    ASSERT ((BaseAddress & (SIZE_4KB - 1)) == 0);
    ASSERT ((Length & (SIZE_4KB - 1)) == 0);

    return RETURN_INVALID_PARAMETER;
  }

  MaximumAddress = (EFI_PHYSICAL_ADDRESS)MAX_UINT32;
  if (BaseAddress > MaximumAddress ||
      Length > MaximumAddress ||
      (BaseAddress > MaximumAddress - (Length - 1))) {
    return RETURN_UNSUPPORTED;
  }


  while (Length != 0) {
    PageEntry = GetPageTableEntry (BaseAddress, &PageAttribute);
    if (PageEntry == NULL) {
      return RETURN_UNSUPPORTED;
    }

    if (PageAttribute != Page4K) {
      Status = SplitPage (PageEntry, PageAttribute, Page4K, FALSE);
      if (RETURN_ERROR (Status)) {
        return Status;
      }


      continue;
    }


    if ((Attributes & IA32_PG_P) != 0) {
      *PageEntry |= (UINT64)IA32_PG_P;
    } else {
      *PageEntry &= ~((UINT64)IA32_PG_P);
    }


    BaseAddress += SIZE_4KB;
    Length -= SIZE_4KB;
  }

  return RETURN_SUCCESS;
}
