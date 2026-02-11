walwrite(Wal *w, job j)
{
    int r = 0;

    if (!w->use) return 1;
    if (w->cur->resv > 0 || usenext(w)) {
        if (j->file) {
            r = filewrjobshort(w->cur, j);
        } else {
            r = filewrjobfull(w->cur, j);
        }
    }
    if (!r) {
        filewclose(w->cur);
        w->use = 0;
    }
    w->nrec++;
    return r;
}
