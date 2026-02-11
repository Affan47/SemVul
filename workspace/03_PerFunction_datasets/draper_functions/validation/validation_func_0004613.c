qif_cat_new(void)
{
    QifObject obj;
    QifCategory cat;

    obj = qif_object_new(struct _QifCategory, QIF_O_CATEGORY, qif_cat_destroy);
    cat = (QifCategory)obj;
    cat->budget = gnc_numeric_zero();

    return cat;
}
