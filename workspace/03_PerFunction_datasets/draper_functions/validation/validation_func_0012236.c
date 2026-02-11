_addVirtualFnsFromSlots(TYPEMAKER2_BUILDER *tb, TYPEMAKER2_TYPE *ty) {
  GWEN_BUFFER *tbuf;
  const char *s;
  TYPEMAKER2_VIRTUALFN_LIST *fnList;
  TYPEMAKER2_SLOT_LIST *slotList;

  tbuf=GWEN_Buffer_new(0, 256, 0, 1);
  fnList=Typemaker2_Type_GetVirtualFns(ty);

  slotList=Typemaker2_Type_GetSlots(ty);
  if (slotList) {
    TYPEMAKER2_SLOT *slot;

    slot=Typemaker2_Slot_List_First(slotList);
    while(slot) {
      TYPEMAKER2_VIRTUALFN *fn;
      TYPEMAKER2_VIRTUALFN_PARAM_LIST *plist;


      s=Typemaker2_Slot_GetName(slot);
      GWEN_Buffer_AppendByte(tbuf, tolower(*s));
      GWEN_Buffer_AppendString(tbuf, s+1);

      fn=Typemaker2_VirtualFn_new();
      plist=Typemaker2_VirtualFn_GetParamTypeList(fn);


      Typemaker2_VirtualFn_SetName(fn, GWEN_Buffer_GetStart(tbuf));

      s=Typemaker2_Slot_GetParamType1(slot);
      if (s && *s && strcasecmp(s, "none")) {
        TYPEMAKER2_VIRTUALFN_PARAM *prm;

        prm=Typemaker2_VirtualFn_Param_new();
        Typemaker2_VirtualFn_Param_SetType(prm, s);
        Typemaker2_VirtualFn_Param_List_Add(prm, plist);
      }
      s=Typemaker2_Slot_GetParamType2(slot);
      if (s && *s && strcasecmp(s, "none")) {
        TYPEMAKER2_VIRTUALFN_PARAM *prm;

        prm=Typemaker2_VirtualFn_Param_new();
        Typemaker2_VirtualFn_Param_SetType(prm, s);
        Typemaker2_VirtualFn_Param_List_Add(prm, plist);
      }
      if (Typemaker2_Slot_GetFlags(slot) & TYPEMAKER2_SLOT_FLAGS_USE_PARAM3) {
        TYPEMAKER2_VIRTUALFN_PARAM *prm;

        prm=Typemaker2_VirtualFn_Param_new();
        Typemaker2_VirtualFn_Param_SetType(prm, "int");
        Typemaker2_VirtualFn_Param_List_Add(prm, plist);
      }
      if (Typemaker2_Slot_GetFlags(slot) & TYPEMAKER2_SLOT_FLAGS_USE_PARAM4) {
        TYPEMAKER2_VIRTUALFN_PARAM *prm;

        prm=Typemaker2_VirtualFn_Param_new();
        Typemaker2_VirtualFn_Param_SetType(prm, "int");
        Typemaker2_VirtualFn_Param_List_Add(prm, plist);
      }

      Typemaker2_VirtualFn_SetAccess(fn, TypeMaker2_Access_Public);
      Typemaker2_VirtualFn_SetLocation(fn, "post");
      Typemaker2_VirtualFn_SetReturnType(fn, "int");
      Typemaker2_VirtualFn_SetDefaultReturnValue(fn, "GWEN_ERROR_NOT_IMPLEMENTED");

      Typemaker2_VirtualFn_AddFlags(fn, TYPEMAKER2_VIRTUALFN_FLAGS_FROMSLOT);

      Typemaker2_VirtualFn_List_Add(fn, fnList);

      slot=Typemaker2_Slot_List_Next(slot);
    }
  }
  GWEN_Buffer_free(tbuf);

  return 0;
}
