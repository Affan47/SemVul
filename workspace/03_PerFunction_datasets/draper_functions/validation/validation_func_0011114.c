qmonCreateARCU(
Widget parent,
XtPointer cld
) {
   Widget   arcu_ok, arcu_cancel, arcu_save, arcu_folder,
            arfield_add, arfield_remove;
   Widget run_m;
   Widget pen_m;
   int i;

   DENTER(GUI_LAYER, "qmonCreateARCU");


   arcu = XmtBuildQueryDialog(parent, "arcu_shell",
                           NULL, 0,
                           "arcu_folder", &arcu_folder,
                           "arfield_selected", &arfield_selected,
                           "arfield_available", &arfield_available,
                           "arfield_add", &arfield_add,
                           "arfield_remove", &arfield_remove,
                           "arcu_ok", &arcu_ok,
                           "arcu_cancel", &arcu_cancel,
                           "arcu_save", &arcu_save,
                           NULL);


   ARColumnPrintHashTable = sge_htable_create(5, dup_func_u_long32, hash_func_u_long32, hash_compare_u_long32);
   for (i=0; i<sizeof(ar_items)/sizeof(tARField); i++) {
      u_long32 temp = XrmStringToQuark(ar_items[i].name);
      sge_htable_store(ARColumnPrintHashTable,
                     &temp,
                     (void *)&ar_items[i]);
   }


   NameMappingHashTable = sge_htable_create(5, dup_func_u_long32, hash_func_u_long32, hash_compare_u_long32);
   for (i=0; i<sizeof(ar_items)/sizeof(tARField); i++) {
      String text;
      u_long32 temp;
      XmString xstr = XmtCreateLocalizedXmString(arcu, ar_items[i].name);
      XmStringGetLtoR(xstr, XmFONTLIST_DEFAULT_TAG, &text);
      temp = XrmStringToQuark(text);
      sge_htable_store(NameMappingHashTable,
                     &temp,
                     (void *)&ar_items[i]);
      XmStringFree(xstr);
      XtFree(text);
   }


   if (qmonGetPreferences()) {
      lListElem *field;
      tARField *ar_item = NULL;
      lList *ar_filter_field_list = lGetList(qmonGetPreferences(), PREF_ar_filter_fields);

      arfilter_fields = lCopyList("", ar_filter_field_list);


      for_each(field, arfilter_fields) {
         u_long32 temp = XrmStringToQuark(lGetString(field, ST_name));
         if (sge_htable_lookup(ARColumnPrintHashTable,
             &temp,
             (const void **) &ar_item)) {
            ar_item->show = 1;
         }
      }
   }


   qmonWhatSetItems(arfield_available, FILL_ALL);
   qmonWhatSetItems(arfield_selected, FILL_SELECTED);


   qmonARReturnMatrix(&run_m, &pen_m);
   SetARLabels(run_m);
#ifdef AR_PENDING
   SetARLabels(pen_m);
#endif


   XtAddCallback(arcu_ok, XmNactivateCallback,
                        okCB, NULL);
   XtAddCallback(arcu_cancel, XmNactivateCallback,
                        cancelCB, NULL);
   XtAddCallback(arcu_save, XmNactivateCallback,
                        saveCB, NULL);
   XtAddCallback(arfield_add, XmNactivateCallback,
                        addToSelected, (XtPointer) arfield);
   XtAddCallback(arfield_remove, XmNactivateCallback,
                        rmFromSelected, (XtPointer) arfield);

   DEXIT;
}
