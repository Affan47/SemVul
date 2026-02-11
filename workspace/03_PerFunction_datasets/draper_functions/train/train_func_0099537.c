qmonHostHelp(Widget w, XtPointer cld, XtPointer cad)
{
   Widget widget = 0;

   DENTER(GUI_LAYER, "qmonHostHelp");

   switch(dialog_mode) {
      case SGE_AH_LIST:
         widget = adminhost_list;
         break;
      case SGE_SH_LIST:
         widget = submithost_list;
         break;
      case SGE_HGRP_LIST:
         widget = hostgroup_list;
         break;
      case SGE_EH_LIST:
         widget = exechost_list;
         break;
   }

   XmtHelpDisplayContextHelp(widget);

   DEXIT;
}
