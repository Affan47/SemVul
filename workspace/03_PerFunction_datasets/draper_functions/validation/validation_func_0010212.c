computeVisibleTraits()
{
    bool modified;

    do {
        modified = false;
        for (set<trait>::iterator p = fTraits.begin(); p != fTraits.end(); p++) {
            if (fWithInput.count(*p) == 0) {
                if (fOutputs.count(p->start) > 0) {
                    fWithInput.insert(*p);
                    fOutputs.insert(p->end);
                    modified = true;
                }
            }
            if (fWithOutput.count(*p) == 0) {
                if (fInputs.count(p->end) > 0) {
                    fWithOutput.insert(*p);
                    fInputs.insert(p->start);
                    modified = true;
                }
            }
        }
    } while (modified);
}
