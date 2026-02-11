defaults() {
  for(int cat = 0; cat < rowCount(); cat++) {
    QModelIndex catidx = index(cat, 0);
    for(int act = 0; act < rowCount(catidx); act++) {
      QModelIndex actidx = index(act, 1, catidx);
      setData(actidx, actidx.data(DefaultShortcutRole), ActiveShortcutRole);
    }
  }
}
