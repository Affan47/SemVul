EnablePaging (
  VOID
  )
{
  UINTN                       PageTable;

  PageTable = CreatePageTable ();
  ASSERT (PageTable != 0);
  if (PageTable != 0) {
    AsmWriteCr3(PageTable);
    AsmWriteCr4 (AsmReadCr4 () | BIT5);
    AsmWriteCr0 (AsmReadCr0 () | BIT31);
  }
}
