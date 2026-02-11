LayoutSectionOnce(MCAsmLayout &Layout,
                                    MCSectionData &SD) {
  MCFragment *FirstInvalidFragment = NULL;

  for (MCSectionData::iterator it2 = SD.begin(),
         ie2 = SD.end(); it2 != ie2; ++it2) {

    bool relaxedFrag = false;
    switch(it2->getKind()) {
    default:
          break;
    case MCFragment::FT_Inst:
      relaxedFrag = RelaxInstruction(Layout, *cast<MCInstFragment>(it2));
      break;
    case MCFragment::FT_Dwarf:
      relaxedFrag = RelaxDwarfLineAddr(Layout,
                                       *cast<MCDwarfLineAddrFragment>(it2));
      break;
    case MCFragment::FT_DwarfFrame:
      relaxedFrag =
        RelaxDwarfCallFrameFragment(Layout,
                                    *cast<MCDwarfCallFrameFragment>(it2));
      break;
    case MCFragment::FT_LEB:
      relaxedFrag = RelaxLEB(Layout, *cast<MCLEBFragment>(it2));
      break;
    }

    if (relaxedFrag && !FirstInvalidFragment)
      FirstInvalidFragment = it2;
  }
  if (FirstInvalidFragment) {
    Layout.Invalidate(FirstInvalidFragment);
    return true;
  }
  return false;
}
