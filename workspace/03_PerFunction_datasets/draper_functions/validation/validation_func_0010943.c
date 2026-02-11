change_tab(XmTabWidget wid, Widget new_tab)
{

   XmTabConstraintRec *tab_constraint;
   int i;
   Widget child;
   int row_active;


   if (XtIsRealized(wid->tab.active_tab))
      XtUnmapWidget(wid->tab.active_tab);

   wid->tab.active_tab = new_tab;
   XtManageChild(new_tab);

   for (i=0; i<wid->composite.num_children; i++)
      if (wid->tab.active_tab == wid->composite.children[i])
         break;

   if (wid->tab.tabs_per_row) {
      row_active = (i / wid->tab.tabs_per_row);
   }
   else {
      row_active = 0;
      wid->tab.tabs_per_row = wid->composite.num_children;
   }

   if ((wid->tab.tab_rows-1) != row_active) {
      for (i=0; i<wid->composite.num_children; i++) {
         child = wid->composite.children[i];
         tab_constraint = (XmTabConstraintRec *) child->core.constraints;
         if (i/wid->tab.tabs_per_row == row_active) {
            tab_constraint->tab.tab_rect.y = (wid->tab.tab_rows-1) *
                                             wid->tab.tab_height;
         }
         if (i/wid->tab.tabs_per_row == (wid->tab.tab_rows-1)) {
            tab_constraint->tab.tab_rect.y = row_active *
                                             wid->tab.tab_height;
         }
      }
   }

}
