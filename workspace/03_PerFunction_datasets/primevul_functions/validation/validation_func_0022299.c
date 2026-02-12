lp_use_properties(struct lp_style_type *lp, int tag)
{


    struct linestyle_def *this;
    int save_flags = lp->flags;

    this = first_linestyle;
    while (this != NULL) {
	if (this->tag == tag) {
	    *lp = this->lp_properties;
	    lp->flags = save_flags;
	    return;
	} else {
	    this = this->next;
	}
    }


    load_linetype(lp, tag);
}
