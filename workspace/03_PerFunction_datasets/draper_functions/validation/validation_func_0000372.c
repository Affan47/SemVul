idealWidth(void) const
{
  int offset=highlightThickness()+shadowThickness()+margin();
  int w=(vectorWidth()+2*innerWidth()+(columns()-1)*columnSpacing()+2*offset);
  if (label()->mapped()==MSTrue)
   {
     int lw=label()->width()+2*offset;
     if ((titleAlignment()&MSLeft)||(titleAlignment()&MSRight))
     lw+=(2*XTextWidth(fontManager()->fontStruct(label()->font()),"M",1));
     return (w>lw)?w:lw;
   }
  else return w;
}
