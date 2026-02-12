void GfxPath::close()
{


    if (justMoved) {
        if (n >= size) {
            size *= 2;
            subpaths = (GfxSubpath **)greallocn(subpaths, size, sizeof(GfxSubpath *));
        }
        subpaths[n] = new GfxSubpath(firstX, firstY);
        ++n;
        justMoved = false;
    }
    subpaths[n - 1]->close();
}
