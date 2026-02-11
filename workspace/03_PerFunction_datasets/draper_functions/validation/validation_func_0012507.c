wheelEvent(QWheelEvent *event) {
	int numDegrees = event->delta() / 8;
	int numSteps = numDegrees / 15;

	int newIndex = currentIndex() - numSteps;

	while (newIndex < 0) {
		newIndex += count();
	}
	newIndex = newIndex % count();

	setCurrentIndex(newIndex);

	event->accept();
}
