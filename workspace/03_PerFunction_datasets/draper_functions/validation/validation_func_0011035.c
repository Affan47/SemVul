doOptionsDialog (bool changePuzzle)
{
    int result = QDialog::Rejected;
    if (tooBusy())
	return (result);
    int optionTemp [nOptions];

    LOOP (n, nOptions) {
	optionTemp [n] = option [n];
    }


    GameDialog * d = new GameDialog (changePuzzle, optionTemp, myParent);

    int count = 0;
    result = QDialog::Accepted;
    while ((result = d->exec()) == QDialog::Accepted) {

	count = 0;
	LOOP (axis, nAxes) {
	    if (optionTemp [optXDim + axis] == 1) {
		count++;
	    }
	}


	if (count > 1) {
	    KMessageBox::information (myParent,
		    i18n("Only one of your dimensions can be one cubie wide."),
		    i18n("Cube Options"));
	    continue;
	}
	else {
	    break;
	}
    }

    if (result == QDialog::Accepted) {
	LOOP (n, nOptions) {
	    option [n] = optionTemp [n];
	}
	moveSpeed = option [optMoveSpeed];
	gameGLView->setBevelAmount (option [optBevel]);
	viewShuffle = (bool) option [optViewShuffle];
	viewMoves = (bool) option [optViewMoves];
	mainWindow->setToggle ("watch_shuffling", (bool)option[optViewShuffle]);
	mainWindow->setToggle ("watch_moves",     (bool)option[optViewMoves]);
    }

    delete d;

    return (result);
}
