GetSubSampler(int num, int count) {
    int x0, x1, y0, y1;
    ComputeSubWindow(num, count, &x0, &x1, &y0, &y1);
    if (x0 == x1 || y0 == y1) return NULL;
    return new AdaptiveSampler(x0, x1, y0, y1, minSamples, maxSamples,
        method == ADAPTIVE_CONTRAST_THRESHOLD ? "contrast" : "shapeid",
        shutterOpen, shutterClose);
}
