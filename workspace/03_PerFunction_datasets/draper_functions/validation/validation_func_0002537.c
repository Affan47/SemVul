collectFemaleConnectees(QSet<ItemBase *> & items) {
	bool hasMale = PaletteItemBase::collectFemaleConnectees(items);
	foreach (ItemBase * lkpi, m_layerKin) {
		if (lkpi->collectFemaleConnectees(items)) {
			hasMale = true;
		}
	}
	return hasMale;
}
