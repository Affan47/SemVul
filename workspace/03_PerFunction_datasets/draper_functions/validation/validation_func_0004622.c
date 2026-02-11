remove(TrayApp *tapp) {
    fCount--;

    if (tapp->getPrev())
        tapp->getPrev()->setNext(tapp->getNext());
    else
        fFirst = tapp->getNext();

    if (tapp->getNext())
        tapp->getNext()->setPrev(tapp->getPrev());
    else
        fLast = tapp->getPrev();
}
