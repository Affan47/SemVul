static double mp_ioff(_cimg_math_parser& mp) {
        const unsigned int
          boundary_conditions = (unsigned int)_mp_arg(3);
        const CImg<T> &img = mp.imgin;
        const longT
          off = (longT)_mp_arg(2),
          whds = (longT)img.size();
        if (off>=0 && off<whds) return (double)img[off];
        if (img._data) switch (boundary_conditions) {
          case 3 : {
            const longT whds2 = 2*whds, moff = cimg::mod(off,whds2);
            return (double)img[moff<whds?moff:whds2 - moff - 1];
          }
          case 2 :
            return (double)img[cimg::mod(off,whds)];
          case 1 :
            return (double)img[off<0?0:whds - 1];
          default :
            return 0;
          }
        return 0;
}
