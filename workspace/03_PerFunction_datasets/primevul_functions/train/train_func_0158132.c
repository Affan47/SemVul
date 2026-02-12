substituteOverrideKeys(DcmDataset *dset)
{
    if (overrideKeys == NULL) {
        return;
    }


    DcmDataset keys(*overrideKeys);


    unsigned long elemCount = keys.card();
    for (unsigned long i = 0; i < elemCount; i++) {
        DcmElement *elem = keys.remove(OFstatic_cast(unsigned long, 0));

        dset->insert(elem, OFTrue);
    }
}
