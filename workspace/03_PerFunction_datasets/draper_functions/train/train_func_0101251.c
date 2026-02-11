qmonShareTreeCut(Widget w, XtPointer cld, XtPointer cad)
{
   Widget tree = (Widget)cld;
   ListTreeItem *item = NULL;
   ListTreeMultiReturnStruct ret;
   tSTNUserData *data;

   DENTER(GUI_LAYER, "qmonShareTreeCut");

   ListTreeGetHighlighted(tree, &ret);
   if (ret.count <= 0) {
      DEXIT;
      return;
   }
   item = ret.items[0];


   if (item && item->parent && item->parent->text && !strcasecmp(item->parent->text, "default")) {
      DEXIT;
      return;
   }

   if (item != ListTreeFirstItem(tree)) {
      paste_tree = lCreateElemList("Tree", STN_Type, 1);
      if (paste_tree) {
         lSetString(lFirst(paste_tree), STN_name, item->text);
         data = (tSTNUserData*)(item->user_data);
         lSetUlong(lFirst(paste_tree), STN_shares, data->share);
         lSetList(lFirst(paste_tree), STN_children, TreeToCull(tree, item));
         XtSetSensitive(st_cut, False);
         XtSetSensitive(st_copy, False);
         XtSetSensitive(st_paste, True);
      }
      ListTreeDelete(tree, item);
      dirty = True;
   }
   else {
      qmonMessageShow(w, True, "@{Can't cut the whole tree !}");
   }

   DEXIT;
}
