updateNetWMStrut() {
    int l, r, t, b;
    client()->getNetWMStrut(&l, &r, &t, &b);
    if (l != fStrutLeft ||
        r != fStrutRight ||
        t != fStrutTop ||
        b != fStrutBottom)
    {
        fStrutLeft = l;
        fStrutRight = r;
        fStrutTop = t;
        fStrutBottom = b;
        MSG(("strut: %d %d %d %d", l, r, t, b));
        manager->updateWorkArea();
    }
}
