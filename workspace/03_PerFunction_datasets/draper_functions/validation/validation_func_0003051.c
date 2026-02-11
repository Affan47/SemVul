SetKey(EEventMap *aMap, const char *aKey) {
    EKeyMap **map = &aMap->KeyMap, *pm, *parent = 0;
    EKey *k;
    char Key[256];
    char *p, *d;
    EEventMap *xm = aMap;


    strcpy(Key, aKey);


    while (xm && xm->Parent && (parent == 0)) {
        parent = xm->Parent->KeyMap;

        xm = xm->Parent;
    }

    d = Key;
    while (d) {

        p = d;
        d = strchr(p, '_');
        if (d) {
            if (d[1] == 0 || d[1] == '_')
                d++;

            if (*d == 0)
                d = 0;
            else {
                *d = 0;
                d++;
            }
        }


        if (d == 0) {
            k = new EKey(p);
            if (*map) {
                (*map)->AddKey(k);
            } else {
                *map = new EKeyMap();
                (*map)->fParent = parent;
                (*map)->AddKey(k);
            }
            return k;

        } else {


            if (*map == 0) {

                k = new EKey(p, 0);
                *map = new EKeyMap();
                (*map)->fParent = parent;
                (*map)->AddKey(k);
            } else {
                KeySel ks;

                ParseKey(p, ks);
                if ((k = (*map)->FindKey(ks.Key)) == 0) {

                    k = new EKey(p, 0);
                    (*map)->AddKey(k);
                }
            }
            map = &k->fKeyMap;


            pm = parent;
            parent = 0;

            while (pm) {
                KeySel ks;
                EKey *pk;

                ParseKey(p, ks);
                if ((pk = pm->FindKey(ks.Key)) != 0) {
                    parent = pk->fKeyMap;

                    break;
                }
                pm = pm->fParent;
            }
        }
    }
    return 0;
}
