cursorRide()
{
    if (active ==  true) return;
    else active = true;
    selectRide(tableView->currentIndex());
    active = false;
}
