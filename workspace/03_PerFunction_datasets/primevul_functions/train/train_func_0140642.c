CreatePageTable (
  VOID
  )
{
  RETURN_STATUS           Status;
  UINTN                   PhysicalAddressBits;
  UINTN                   NumberOfEntries;
  PAGE_ATTRIBUTE          TopLevelPageAttr;
  UINTN                   PageTable;
  PAGE_ATTRIBUTE          MaxMemoryPage;
  UINTN                   Index;
  UINT64                  AddressEncMask;
  UINT64                  *PageEntry;
  EFI_PHYSICAL_ADDRESS    PhysicalAddress;

  TopLevelPageAttr = (PAGE_ATTRIBUTE)GetPageTableTopLevelType ();
  PhysicalAddressBits = GetPhysicalAddressWidth ();
  NumberOfEntries = (UINTN)1 << (PhysicalAddressBits -
                                 mPageAttributeTable[TopLevelPageAttr].AddressBitOffset);

  PageTable = (UINTN) AllocatePageTableMemory (1);
  if (PageTable == 0) {
    return 0;
  }

  AddressEncMask = PcdGet64 (PcdPteMemoryEncryptionAddressOrMask);
  AddressEncMask &= mPageAttributeTable[TopLevelPageAttr].AddressMask;
  MaxMemoryPage = GetMaxMemoryPage (TopLevelPageAttr);
  PageEntry = (UINT64 *)PageTable;

  PhysicalAddress = 0;
  for (Index = 0; Index < NumberOfEntries; ++Index) {
    *PageEntry = PhysicalAddress | AddressEncMask | PAGE_ATTRIBUTE_BITS;


    if (MaxMemoryPage < TopLevelPageAttr) {
      Status = SplitPage(PageEntry, TopLevelPageAttr, MaxMemoryPage, TRUE);
      ASSERT_EFI_ERROR (Status);
    }

    if (TopLevelPageAttr == Page1G) {


      *PageEntry &= ~(UINT64)(IA32_PG_RW | IA32_PG_U);
    }

    PageEntry += 1;
    PhysicalAddress += mPageAttributeTable[TopLevelPageAttr].Length;
  }


  return PageTable;
}
