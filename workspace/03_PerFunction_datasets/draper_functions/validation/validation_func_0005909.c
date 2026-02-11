next(FieldPosition& fp) {
  if (pos == -1) {
    return FALSE;
  }

  fp.setField(data->elementAti(pos++));
  fp.setBeginIndex(data->elementAti(pos++));
  fp.setEndIndex(data->elementAti(pos++));

  if (pos == data->size()) {
    pos = -1;
  }

  return TRUE;
}
