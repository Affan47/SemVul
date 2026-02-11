xcfOffset(uint32_t addr,int spaceafter)
{
  uint32_t apparent ;
  xcfCheckspace(addr,4,"(xcfOffset)");
  apparent = xcfL(addr);
  xcfCheckspace(apparent,spaceafter,
                "Too large offset (%" PRIX32 ") at position %" PRIX32,
                apparent,addr);
  return apparent ;
}
