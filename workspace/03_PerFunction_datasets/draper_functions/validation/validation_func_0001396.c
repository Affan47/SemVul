find(Display* d) {
    if (info_list_ == nil) {
	info_list_ = new PainterDpyInfoList(3);
    }
    for (ListItr(PainterDpyInfoList) i(*info_list_); i.more(); i.next()) {
	PainterDpyInfo* p = i.cur();
	if (p->display_ == d) {
	    return p;
	}
    }
    PainterDpyInfo* p = new PainterDpyInfo;
    p->display_ = d;
    p->btable_ = nil;
    p->txtable_ = nil;
    p->tx_rasters_ = nil;
    p->txfonts = PainterDpyInfo::TxFontsDefault;
    p->tximages = PainterDpyInfo::TxImagesDefault;

    String v;
    if (d->style()->find_attribute("TransformFonts", v)) {
	if (v.case_insensitive_equal("on")) {
	    p->txfonts = PainterDpyInfo::TxFontsOn;
	} else if (v.case_insensitive_equal("off")) {
	    p->txfonts = PainterDpyInfo::TxFontsOff;
	} else if (v.case_insensitive_equal("cache")) {
	    p->txfonts = PainterDpyInfo::TxFontsCache;
	}
    }
    if (d->style()->find_attribute("TransformImages", v)) {
	if (v.case_insensitive_equal("auto")) {
	    p->tximages = PainterDpyInfo::TxImagesAuto;
	} else if (v.case_insensitive_equal("off")) {
	    p->tximages = PainterDpyInfo::TxImagesDest;
	} else if (v.case_insensitive_equal("source")) {
	    p->tximages = PainterDpyInfo::TxImagesSource;
	}
    }
    info_list_->append(p);
    return p;
}
