computeSize(void)
{
  if (MSRect::width()!=0&&MSRect::height()!=0)
   {
    int offset=_owner->highlightThickness()+_owner->shadowThickness();
    computeArrowRects();
    offsetArrow(MSRect::x()-offset,MSRect::y()-offset);
  }
}
