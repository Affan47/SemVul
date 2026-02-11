HalfImageSize(const Image& image)
{
    int rows, cols, nrows, ncols, r, c, ri, ci;

    Image newimage;

    rows = image.rows;
    cols = image.cols;
    nrows = rows / 2;
    ncols = cols / 2;
    newimage.setSize(nrows, ncols);
    const FloatMatrix& im = image.pixels;
    FloatMatrix& _new = newimage.pixels;

    for (r = 0, ri = 0; r < nrows; r++, ri += 2)
        for (c = 0, ci = 0; c < ncols; c++, ci += 2)
            _new[r][c] = im[ri][ci];
    return newimage;
}
