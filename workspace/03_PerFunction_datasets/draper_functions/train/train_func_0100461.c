do_oname(struct obj *obj)
{
    char buf[BUFSZ], qbuf[QBUFSZ];
    const char *aname;
    short objtyp;

    sprintf(qbuf, "What do you want to name %s %s?",
            is_plural(obj) ? "these" : "this", xname(obj));
    getlin(qbuf, buf);
    if(!*buf || *buf == '\033')	return;

    mungspaces(buf);


    if ((aname = artifact_name(buf, &objtyp)) != 0 && objtyp == obj->otyp)
            strcpy(buf, aname);

    if (obj->oartifact) {
        pline_The("artifact seems to resist the attempt.");
        return;
    } else if (restrict_name(obj, buf) || exist_artifact(obj->otyp, buf)) {
        int n = rn2((int)strlen(buf));
        char c1, c2;

        c1 = lowc(buf[n]);
        do c2 = 'a' + rn2('z'-'a'); while (c1 == c2);
        buf[n] = (buf[n] == c1) ? c2 : highc(c2);
        pline("While engraving your %s slips.", body_part(HAND));
        display_nhwindow(WIN_MESSAGE, false);
        You("engrave: \"%s\".",buf);
    }
    obj = oname(obj, buf);
}
