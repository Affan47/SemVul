int COLOR(int row, int col)
  {
    if (!imgdata.idata.filters)
      return 6;
    if (imgdata.idata.filters < 1000)
      return fcol(row, col);
    return libraw_internal_data.internal_output_params.fuji_width
               ? FCF(row, col)
               : FC(row, col);
  }
