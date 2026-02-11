qmonCreateCalendarAsk(
Widget parent
) {
   Widget cal_ok, cal_cancel;

   DENTER(GUI_LAYER, "qmonCreateCalendarAsk");

   cal_ask_layout = XmtBuildQueryDialog( parent, "cal_ask_shell",
                           NULL, 0,
                           "cal_ok", &cal_ok,
                           "cal_cancel", &cal_cancel,
                           "cal_name", &cal_name_w,
                           "cal_year", &cal_year_w,
                           "cal_week", &cal_week_w,
                           NULL);

   XtAddCallback(cal_ok, XmNactivateCallback,
                     qmonCalendarOk, NULL);
   XtAddCallback(cal_cancel, XmNactivateCallback,
                     qmonCalendarCancel, NULL);

   XtAddEventHandler(XtParent(cal_ask_layout), StructureNotifyMask, False,
                        SetMinShellSize, NULL);
   XtAddEventHandler(XtParent(cal_ask_layout), StructureNotifyMask, False,
                        SetMaxShellSize, NULL);

   DEXIT;
   return cal_ask_layout;
}
