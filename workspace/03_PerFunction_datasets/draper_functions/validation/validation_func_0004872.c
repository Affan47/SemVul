loadCharSetCombos()
{
  charSets = getCharSets();

  ui.inputCharSetCombo->clear();
  ui.outputCharSetCombo->clear();
  ui.inputCharSetCombo->addItem(tr("default"), QVariant(-1));
  ui.outputCharSetCombo->addItem(tr("default"), QVariant(-1));
  for (int i=0; i<charSets.size(); i++) {
    ui.inputCharSetCombo->addItem(charSets[i], QVariant(i));
    ui.outputCharSetCombo->addItem(charSets[i], QVariant(i));
  }
}
