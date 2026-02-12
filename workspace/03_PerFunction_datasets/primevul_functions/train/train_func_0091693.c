bool __fastcall TSCPFileSystem::IsTotalListingLine(const UnicodeString Line)
{


  return !Line.SubString(1, 5).CompareIC(L"total");
}
