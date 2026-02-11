event(QEvent *event) {

	if (event->type() == QEvent::KeyPress) {
		QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
		if(keyEvent->matches(QKeySequence::MoveToNextLine) || keyEvent->matches(QKeySequence::SelectNextLine) ||
		   keyEvent->matches(QKeySequence::MoveToPreviousLine) || keyEvent->matches(QKeySequence::SelectPreviousLine) ||
		   keyEvent->matches(QKeySequence::MoveToNextPage) ||  keyEvent->matches(QKeySequence::SelectNextPage) ||
		   keyEvent->matches(QKeySequence::MoveToPreviousPage) ||  keyEvent->matches(QKeySequence::SelectPreviousPage)
		   )
		{
			if(d->listWidget) {
				QApplication::sendEvent(d->listWidget, event);
				return true;
			}
		}
		else if(keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return ) {
			if(!trapReturnKey() ) {
                                if(d->listWidget) {
                                        QApplication::sendEvent(d->listWidget, event);
                                        return true;
                                }
			}
		}
	}
	return KLineEdit::event(event);
}
