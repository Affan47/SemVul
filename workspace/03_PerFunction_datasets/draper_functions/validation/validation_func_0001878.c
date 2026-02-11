show_remove(int charsToDelete, int showposition) {
    AD_ERR *ad_err;
    int realposition = adt_ali->gap_realpos(showposition);
    if ((realposition < 0) || (charsToDelete<0) || (charsToDelete > seq_len) || (showposition >= seq_len)) {
        return new AD_ERR("ADT_SEQ.remove() WARNING ! Wrong Parameters !");
    }
    if (adt_ali->gap_behind(realposition) == 1) {
        return new AD_ERR("ADT_SEQUENCE::show_remove  -- not allowed because Gap behind position");
    }
    if (show_timestamp != timestamp) {
        return new AD_ERR("ADT_SEQUENCE::show_remove  -- not allowed -- because timeupdate not done !");
    }
    ad_err = this->remove(charsToDelete,realposition,1);
    if (!ad_err) this->show_update();
    return ad_err;
}
