IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Parameters") {
        plString typeStr = tag->getParam("Type", "");
        fType = hsKeyFrame::kUnknownKeyFrame;
        for (size_t i=0; i<=hsKeyFrame::kMatrix44KeyFrame; i++) {
            if (typeStr == hsKeyFrame::TypeNames[i])
                fType = i;
        }
        fUruUnknown = tag->getParam("UruUnknown", "0").toUint();
    } else if (tag->getName() == "Keys") {
        AllocKeys(tag->countChildren(), fType);
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fKeys.getSize(); i++) {
            fKeys[i]->prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "EaseControllers") {
        AllocControllers(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fEaseControllers.getSize(); i++) {
            fEaseControllers[i]->prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}
