computeBreaks(void)
{
  clearBreaks();
  grandTotal()=0;
  breakIndex().removeAll();
  pageBreakIndex().removeAll();
  breakColumn().removeAll();
  breakTextColumn().removeAll();

  int n=numColumns()-1;
  if(n<0) return;
  for (unsigned i=0;i<numRows()+1;i++)
    {
      for (unsigned j=n;j<=n;j--)
       {
	MSTableColumn *field=reportColumn(j);
	if (field!=0&&field->breakOn()==MSTrue&&
	    ((i<field->numRows()&&field->breakCriteria(i)==MSTrue)||i==field->numRows()))
	 {
	   breakIndex()<<i;
	   breakColumn()<<j;
	   if (field->breakTextList().count()>=field->breakIndex().length()) breakTextColumn()<<j;
	   if (field->pageBreakOn()==MSTrue) pageBreakIndex()<<i;
	   field->breakIndex()<<i;
	   breakProcess(field->breakIndex());
	 }
       }
    }
  if (reportTotalOn()==MSTrue||reportGrandTotalOn()==MSTrue)
   {
     computeColumnTotals();
     if (reportTotalOn()==MSTrue)
      {
	breakIndex()<<numRows();
	breakColumn()<<0;
      }
     if (reportGrandTotalOn()==MSTrue)
      {

	if (_grandTotalBaseText!=0) delete _grandTotalBaseText;
	_grandTotalBaseText=new MSParagraph(grandTotalText());
	MSStringVector sv(grandTotalText().text());
        MSFloat aFloat(grandTotal());
        MSString buffer;
        MSFloat::MSFloatFormat format=report()->asciiFloatFormat()!=0?report()->asciiFloatFormat():
          MSFloat::Decimal0;
        aFloat.format(buffer,MSFormat(format));
	if (sv.length()>0) sv[sv.length()-1]<<buffer;
	else sv<<buffer;
	grandTotalBaseText()=sv;
        if (grandTotalBaseText().column()>numColumns()) grandTotalBaseText().column(numColumns()-1);
      }
   }
  breakIndex().sortUp();
  pageBreakIndex().sortUp();
}
