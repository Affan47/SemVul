qmonQCTime(Widget w, XtPointer cld, XtPointer cad)
{
   Widget input_field = (Widget) cld;
   char stringval[256];
   Boolean status = False;
   String current;
   Boolean mode = True;

   DENTER(GUI_LAYER, "qmonQCTime");

   if (input_field == suspend_interval)
      mode = False;

   current = XmtInputFieldGetString(input_field);
   sge_strlcpy(stringval, current, sizeof(stringval));
   status = XmtAskForTime(w, NULL, "@{Enter time}",
               stringval, sizeof(stringval), NULL, mode);
   if (stringval[0] == '\0')
      status = False;

   if (status)
      XmtInputFieldSetString(input_field, stringval);

   DEXIT;
}
