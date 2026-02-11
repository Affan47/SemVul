MapIdToTextProperty(unsigned long id,
                                           vtkTextProperty *tprop)
{
  if (!tprop)
    {
    vtkErrorMacro(<< "Wrong parameters, one of them is NULL");
    return;
    }


  int bits = 1;


  int fam = id >> bits;
  bits += 4;
  tprop->SetFontFamily((fam & ((1 << 4) - 1))+ tprop->GetFontFamilyMinValue());


  int bold = id >> bits;
  bits++;
  tprop->SetBold(bold & 0x1);


  int italic = id >> bits;
  bits++;
  tprop->SetItalic(italic & 0x1);


  int angle = id >> bits;
  tprop->SetOrientation((angle & ((1 << 12) - 1)) / 10.0);


}
