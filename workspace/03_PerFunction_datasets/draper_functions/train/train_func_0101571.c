selectionChanged(const QItemSelection &s)
{
  int row = -1;
  if (s.size() >= 1)
    row = s[0].top();
  selected = -1;
  if (row >= 0 && row <= d->history.size())
    if (! v->isRowHidden(row))
      selected = d->history.size() - row - 1;
  if (d->historyPos != selected)
    d->toHistory(selected);
  hiliteSearch();
}
