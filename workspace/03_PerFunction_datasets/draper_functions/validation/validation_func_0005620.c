dumpAttribute(raw_ostream &OS,
                                               const DWARFCompileUnit *cu,
                                               uint32_t* offset_ptr,
                                               uint16_t attr,
                                               uint16_t form,
                                               unsigned indent) const {
  OS << format("0x%8.8x: ", *offset_ptr);
  OS.indent(indent+2);
  const char *attrString = AttributeString(attr);
  if (attrString)
    OS << attrString;
  else
    OS << format("DW_AT_Unknown_%x", attr);
  const char *formString = FormEncodingString(form);
  if (formString)
    OS << " [" << formString << ']';
  else
    OS << format(" [DW_FORM_Unknown_%x]", form);

  DWARFFormValue formValue(form);

  if (!formValue.extractValue(cu->getDebugInfoExtractor(), offset_ptr, cu))
    return;

  OS << "\t(";
  formValue.dump(OS, cu);
  OS << ")\n";
}
