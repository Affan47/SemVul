getFontName()


{
    int f = family.getValue();
    int s = style.getValue();

    if (family.isIgnored()) f = SERIF;
    if (style.isIgnored()) s = NONE;

    if (f < 0 || f > 2) f = 0;
    if (s < 0 || s > 3) s = 0;

    return fontList[f][s];
}
