ToDisplayString(double numberToConvert,
                                    int digitsAfterDecimalPoint )
{
   wxString decSep = wxString(GetDecimalSeparator());
   wxString result;

   if (digitsAfterDecimalPoint == -1)
   {
      result.Printf(wxT("%f"), numberToConvert);


      result.Replace(wxT("."), decSep);

      if (result.Find(decSep) != -1)
      {

         int pos = result.Length() - 1;
         while ((pos > 1) &&
                  (result.GetChar(pos) == wxT('0')) &&
                  (result.GetChar(pos - 1) != decSep))
            pos--;


         result = result.Left(pos+1);
      }
   }
   else
   {
      wxString format;
      format.Printf(wxT("%%.%if"), digitsAfterDecimalPoint);
      result.Printf(format, numberToConvert);


      result.Replace(wxT("."), decSep);
   }

   return result;
}
