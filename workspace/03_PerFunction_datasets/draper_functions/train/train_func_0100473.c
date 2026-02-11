killBuses(QVector<BusShared *> & buses) {
    foreach (BusShared * bus, buses) {
        delete bus;
    }
    buses.clear();
}
