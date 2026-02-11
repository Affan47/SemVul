convert(A sym_) const
{
  if (!QS(sym_) && sym_->t==Et && sym_->n>0 && QS(*sym_->p))
    {
      return fromString((char *)XS(sym_->p[0])->n);
    }
  else
    {
      return enumNotFound();
    }
}
