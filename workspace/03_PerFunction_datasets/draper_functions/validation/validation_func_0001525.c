IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SittingModParams") {
        fMiscFlags = tag->getParam("MiscFlags", "0").toUint();
    } else if (tag->getName() == "NotifyKeys") {
        fNotifyKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fNotifyKeys.getSize(); i++) {
            fNotifyKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
