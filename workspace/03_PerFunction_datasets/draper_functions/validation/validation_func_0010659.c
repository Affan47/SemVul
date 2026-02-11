showPopup() {
	myTimer = new QTimer(this);
	connect(myTimer, SIGNAL(timeout()), this, SLOT(doShowPopup()));
	myTimer->start(10);
}
