ddjvu_miniexp_release(ddjvu_document_t *document, miniexp_t expr)
{
  miniexp_t q = miniexp_nil;
  miniexp_t p = document->protect;
  while (miniexp_consp(p))
    {
      if (miniexp_car(p) != expr)
        q = p;
      else if (q)
        miniexp_rplacd(q, miniexp_cdr(p));
      else
        document->protect = miniexp_cdr(p);
      p = miniexp_cdr(p);
    }
}
