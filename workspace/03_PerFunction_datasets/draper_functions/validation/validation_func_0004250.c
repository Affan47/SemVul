removeRow(unsigned row_)
{
  if (row_+1>rows()) return *this;
  if (data()==0) return *this;

  unsigned newLength=(rows()-1)*columns();
  MSTypeData<unsigned char,MSAllocator<unsigned char> > *d=MSTypeData<unsigned char,MSAllocator<unsigned char> >::allocateWithLength(newLength);
  unsigned char *dp=d->elements();
  unsigned char *mp=data();
  unsigned i,j;
  for (i=0;i<rows();i++)
   {
     if (i==row_) mp+=columns();
     else for (j=0;j<columns();j++) *dp++=*mp++;
   }
  freeData();
  _pData=d;
  _rows-=1;
  _count=newLength;
  changed();
  return *this;
}
