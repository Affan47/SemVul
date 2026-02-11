qmonDeleteARForMatrix(
Widget w,
Widget matrix,
lList **local
) {
   int i;
   int rows;
   lList *ardl = NULL;
   lList *alp = NULL;
   char *str = NULL;
   int force;

   DENTER(GUI_LAYER, "qmonDeleteARForMatrix");


   force = XmToggleButtonGetState(force_toggle);


   rows = XbaeMatrixNumRows(matrix);
   for (i=0; i<rows; i++) {

      if (XbaeMatrixIsRowSelected(matrix, i)) {
         str = XbaeMatrixGetCell(matrix, i, 0);
         if (str && *str != '\0') {
            DPRINTF(("ARId to delete: %s\n", str));
            lAddElemStr(&ardl, ID_str, str, ID_Type);
         }
      }
      if (force != 0) {
         lListElem *id;
         for_each(id, ardl){
            lSetUlong(id, ID_force, force);
         }
      }
   }

   if (ardl) {
      alp = ctx->gdi(ctx, SGE_AR_LIST, SGE_GDI_DEL, &ardl, NULL, NULL);
      qmonMessageBox(w, alp, 0);
      lFreeList(&alp);

      updateARList();
      XbaeMatrixDeselectAll(matrix);

      lFreeList(&ardl);
   }
#if 0
   else {
      qmonMessageShow(w, True, "@{There are no ARs selected !}");
      DEXIT;
      return False;
   }
#endif

   DEXIT;
   return True;
}
