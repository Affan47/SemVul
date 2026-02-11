partLabelEdit()
{
	bool ok;
	QString oldText = m_text;
    QString text = QInputDialog::getText((QGraphicsView *) this->scene()->parent(), tr("Set label for %1").arg(m_owner->title()),
                                          tr("Label text:"), QLineEdit::Normal, oldText, &ok);
	if (ok && (oldText.compare(text) != 0)) {
		if (m_owner) {
			m_owner->partLabelChanged(text);
			foreach (PartLabel * p, AllPartLabels.values(m_owner->id())) {
				p->setPlainText(text);
			}
		}
	}
}
