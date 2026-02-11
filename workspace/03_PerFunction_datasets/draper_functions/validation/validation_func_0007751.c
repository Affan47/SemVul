moveTo(AP_tree *new_brother, AP_FLOAT rel_pos) {


    awt_assert(father);
    awt_assert(new_brother->father);
    awt_assert(new_brother->father != father);
    awt_assert(!new_brother->is_son(this));

    if (father->leftson != this) father->swap_sons();

    if (father->father == 0) {
        brother()->father = 0;
        tree_root->inform_about_changed_root(father, brother());
    }
    else {
        AP_tree *ff_pntr = father->father;
        if (father == new_brother) {
            new_brother  = brother();
            if (ff_pntr->leftson == father) {
                rel_pos *= ff_pntr->leftlen / (father->rightlen+ff_pntr->leftlen);
            }
            else {
                rel_pos *= ff_pntr->rightlen / (father->rightlen+ff_pntr->rightlen);
            }
        }
        else if (new_brother->father == father) {
            rel_pos =
                1.0 + (rel_pos-1.0) * father->rightlen
                /
                (father->rightlen + (ff_pntr->leftson == father ? ff_pntr->leftlen : ff_pntr->rightlen));
        }

        if (ff_pntr->leftson == father) {
            ff_pntr->leftlen += father->rightlen;
            ff_pntr->leftson  = father->rightson;
            father->rightson->father = ff_pntr;
        }
        else {
            ff_pntr->rightlen += father->rightlen;
            ff_pntr->rightson  = father->rightson;
            father->rightson->father = ff_pntr;
        }
    }

    AP_tree  *new_tree       = father;
    AP_tree  *brother_father = new_brother->father;
    AP_FLOAT  laenge;

    if (brother_father->leftson == new_brother) {
        laenge  = brother_father->leftlen;
        laenge -= brother_father->leftlen = laenge * rel_pos ;
        new_brother->father->leftson = new_tree;
    }
    else {
        laenge  = brother_father->rightlen;
        laenge -= brother_father->rightlen = laenge * rel_pos ;
        brother_father->rightson = new_tree;
    }

    new_tree->rightlen  = laenge;
    new_brother->father = new_tree;
    new_tree->rightson  = new_brother;
    new_tree->father    = brother_father;
}
