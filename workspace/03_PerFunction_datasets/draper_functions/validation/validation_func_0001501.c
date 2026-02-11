Free_QVcoding(QVcoding *coding)
{ if (coding->subChar >= 0)
    free(coding->sRunScheme);
  free(coding->subScheme);
  free(coding->mrgScheme);
  free(coding->insScheme);
  if (coding->delChar >= 0)
    free(coding->dRunScheme);
  free(coding->delScheme);
  free(coding->prefix);
}
