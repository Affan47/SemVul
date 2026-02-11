qmonHostgroupOk(Widget w, XtPointer cld, XtPointer cad)
{
   lList *alp = NULL;
   StringConst hgname = NULL;
   lListElem *hg_ep = NULL;
   lList *href_list = NULL;

   DENTER(GUI_LAYER, "qmonHostgroupOk");


   hgname = XmtInputFieldGetString(hg_name_w);
   if (!hgname || hgname[0] == '\0') {
      qmonMessageShow(w, True, "@{Empty hostgroup name !}");
      DEXIT;
      return;
   }

   href_list = XmStringToCull(hg_memberlist_w, HR_Type, HR_name, ALL_ITEMS);
   hg_ep = hgroup_create(&alp, hgname, href_list, true);

   if (add_mode) {
      hgroup_add_del_mod_via_gdi(ctx, hg_ep, &alp, SGE_GDI_ADD);
   } else {
      hgroup_add_del_mod_via_gdi(ctx, hg_ep, &alp, SGE_GDI_MOD);
   }

   if (lFirst(alp) && lGetUlong(lFirst(alp), AN_status) != STATUS_OK) {
      qmonMessageBox(w, alp, 0);
   } else {
      XtUnmanageChild(hg_ask_layout);
      updateHostListCB(w, NULL, NULL);
   }

   lFreeList(&alp);

   DEXIT;
}
