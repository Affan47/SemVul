qmonARSubPopdown(Widget w, XtPointer cld, XtPointer cad)
{

   DENTER(GUI_LAYER, "qmonARSubPopdown");

   if (qmon_arsub) {
      qmonStopTimer(AR_T | PE_T);
      xmui_unmanage(qmon_arsub);
   }
   DEXIT;
}
