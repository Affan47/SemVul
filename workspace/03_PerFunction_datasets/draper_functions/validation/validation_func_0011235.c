yToRow(int y_)
{
  int row;
  if (y_<0) row=0;
  else if (y_>panner()->height()) row=rows();
  else
   {
     int h=rowHeight();
     int i=firstRow();
     while(h<=y_&&i<=lastRow())
      {
        i++;
        h+=rowHeight();
      }
     row=i-firstRow();
   }
  return (row>=0)?row:0;
}
