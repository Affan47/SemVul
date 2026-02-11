xref_decs (FILE_T f, TABLE_T * t)
{
  if (INDICANTS (t) != NO_TAG) {
    xref_tags (f, INDICANTS (t), INDICANT);
  }
  if (OPERATORS (t) != NO_TAG) {
    xref_tags (f, OPERATORS (t), OP_SYMBOL);
  }
  if (PRIO (t) != NO_TAG) {
    xref_tags (f, PRIO (t), PRIO_SYMBOL);
  }
  if (IDENTIFIERS (t) != NO_TAG) {
    xref_tags (f, IDENTIFIERS (t), IDENTIFIER);
  }
  if (LABELS (t) != NO_TAG) {
    xref_tags (f, LABELS (t), LABEL);
  }
  if (ANONYMOUS (t) != NO_TAG) {
    xref_tags (f, ANONYMOUS (t), ANONYMOUS);
  }
}
