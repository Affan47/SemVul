cpl_polynomial_fit_2d_create(cpl_bivector     *  xy_pos,
                                              cpl_vector       *  values,
                                              cpl_size            degree,
                                              double           *  mse)
{
    cpl_polynomial * self = cpl_polynomial_new(2);
    const cpl_error_code error = cpl_polynomial_fit_2d(self, xy_pos, values,
                                                       CPL_FALSE, &degree, mse);

    if (error != CPL_ERROR_NONE) {
        cpl_polynomial_delete(self);
        self = NULL;
        cpl_error_set_(error);
    }

    return self;

}
