moveLock()
{
	bool moveLock = true;

	foreach (QGraphicsItem  * item, m_currentGraphicsView->scene()->selectedItems()) {
		ItemBase * itemBase = ItemBase::extractTopLevelItemBase(item);
		if (itemBase == NULL) continue;
		if (itemBase->itemType() == ModelPart::Wire) continue;

		if (itemBase->moveLock()) {
			moveLock = false;
			break;
		}
	}

	ItemBase * viewedItem = m_infoView->currentItem();
	foreach (QGraphicsItem  * item, m_currentGraphicsView->scene()->selectedItems()) {
		ItemBase * itemBase = ItemBase::extractTopLevelItemBase(item);
		if (itemBase == NULL) continue;
		if (itemBase->itemType() == ModelPart::Wire) continue;

		itemBase->setMoveLock(moveLock);
		if (viewedItem && viewedItem->layerKinChief() == itemBase->layerKinChief()) {
			m_currentGraphicsView->viewItemInfo(itemBase);
		}
	}
}
