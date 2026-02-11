Emit(const AsmPrinter *AP) const {

  AP->EmitULEB128(Tag, dwarf::TagString(Tag));


  AP->EmitULEB128((unsigned)Children, dwarf::ChildrenString(Children));


  for (unsigned i = 0, N = Data.size(); i < N; ++i) {
    const DIEAbbrevData &AttrData = Data[i];


    AP->EmitULEB128(AttrData.getAttribute(),
                    dwarf::AttributeString(AttrData.getAttribute()));


    AP->EmitULEB128(AttrData.getForm(),
                    dwarf::FormEncodingString(AttrData.getForm()));
  }


  AP->EmitULEB128(0, "EOM(1)");
  AP->EmitULEB128(0, "EOM(2)");
}
