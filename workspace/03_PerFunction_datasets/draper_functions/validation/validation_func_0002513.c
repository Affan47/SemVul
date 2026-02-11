butSet_destroy(ButSet *butset)  {
  if (butset->dynamic && (butset->buts != NULL))
    wms_free(butset->buts);
}
