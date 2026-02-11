FoldDestroyAll() {
    int l;

    if (Modify() == 0) return 0;

    for (l = 0; l < RCount; l++)
        if (FindFold(l) != -1)
            if (FoldDestroy(l) == 0) return 0;
    return 1;
}
