dockChangeActivation(bool activate, QWidget * originator) {
	Q_UNUSED(activate);
	Q_UNUSED(originator);
	if (!m_closing) {
		m_sizeGrip->rearrange();
	}

}
