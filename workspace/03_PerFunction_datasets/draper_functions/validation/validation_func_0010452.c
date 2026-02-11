refreshAscendantMapping(const QModelIndex &index, bool refreshAll)
{
  Q_Q(KRecursiveFilterProxyModel);

  Q_ASSERT(index.isValid());
  QModelIndex lastAscendant = index;
  QModelIndex sourceAscendant = index.parent();


  while(sourceAscendant.isValid() && !q->acceptRow(sourceAscendant.row(), sourceAscendant.parent()))
  {
    if (refreshAll)
      invokeDataChanged(sourceAscendant, sourceAscendant);

    lastAscendant = sourceAscendant;
    sourceAscendant = sourceAscendant.parent();
  }


  invokeDataChanged(lastAscendant, lastAscendant);
}
