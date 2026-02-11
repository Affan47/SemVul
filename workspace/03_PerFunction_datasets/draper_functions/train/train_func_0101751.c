resetDisplay(void) {
    int retval = 0;

    if (duplicate_action[ActionZoom]) {
        for (connectionIterator i = otherimview.begin() ; i != otherimview.end() ; ++i) {
            *((*i)->stream) << "reset" << endl;
            retval = getresponse((*i)->stream);
        }
    } else
        retval = 1;

    return retval;
}
