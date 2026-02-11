reconstruct() {
    unsigned int i;
    int retval;


    if (!bottom_level) {
        int n = 0;
        for (i=0; i<children.size(); i++) {
            META_CHUNK* cp = (META_CHUNK*)children[i];
            if (cp->status == PRESENT) {
                retval = cp->reconstruct();
                if (retval) return retval;
                n++;
                if (n == coding.n) break;
            }
        }
    }
    retval = decode();
    if (retval) return retval;


    for (i=0; i<children.size(); i++) {
        children[i]->delete_file();
    }
    return 0;
}
