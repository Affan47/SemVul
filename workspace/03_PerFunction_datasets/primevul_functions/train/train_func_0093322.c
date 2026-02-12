void standard_eof(abytewriter* hdrw, abytewriter* huffw) {

    hdrdata  = hdrw->getptr_aligned();
    hdrs     = hdrw->getpos();

    huffdata = huffw->getptr_aligned();
    hufs     = huffw->getpos();
}
