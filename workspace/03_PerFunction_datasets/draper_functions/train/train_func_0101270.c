parse(DataExtractor data) {
  uint32_t Offset = 0;
  while (data.isValidOffset(Offset)) {
    Locations.resize(Locations.size() + 1);
    LocationList &Loc = Locations.back();
    Loc.Offset = Offset;
    dwarf::LocationListEntry Kind;
    while ((Kind = static_cast<dwarf::LocationListEntry>(
                data.getU8(&Offset))) != dwarf::DW_LLE_end_of_list_entry) {

      if (Kind != dwarf::DW_LLE_start_length_entry) {
        llvm::errs() << "error: dumping support for LLE of kind " << (int)Kind
                     << " not implemented\n";
        return;
      }

      Entry E;

      E.Start = data.getULEB128(&Offset);
      E.Length = data.getU32(&Offset);

      unsigned Bytes = data.getU16(&Offset);

      StringRef str = data.getData().substr(Offset, Bytes);
      Offset += Bytes;
      E.Loc.resize(str.size());
      std::copy(str.begin(), str.end(), E.Loc.begin());

      Loc.Entries.push_back(std::move(E));
    }
  }
}
