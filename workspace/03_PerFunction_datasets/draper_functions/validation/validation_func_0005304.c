format_float_internal(PyObject *value,
                      const InternalFormatSpec *format)
{
    char *buf = NULL;
    Py_ssize_t n_digits;
    Py_ssize_t n_remainder;
    Py_ssize_t n_total;
    int has_decimal;
    double val;
    Py_ssize_t precision = format->precision;
    Py_ssize_t default_precision = 6;
    Py_UCS4 type = format->type;
    int add_pct = 0;
    Py_ssize_t index;
    NumberFieldWidths spec;
    int flags = 0;
    PyObject *result = NULL;
    Py_UCS4 maxchar = 127;
    Py_UCS4 sign_char = '\0';
    int float_type;
    PyObject *unicode_tmp = NULL;
    int err;


    LocaleInfo locale = STATIC_LOCALE_INFO_INIT;

    if (format->alternate)
        flags |= Py_DTSF_ALT;

    if (type == '\0') {


        flags |= Py_DTSF_ADD_DOT_0;
        type = 'r';
        default_precision = 0;
    }

    if (type == 'n')


        type = 'g';

    val = PyFloat_AsDouble(value);
    if (val == -1.0 && PyErr_Occurred())
        goto done;

    if (type == '%') {
        type = 'f';
        val *= 100;
        add_pct = 1;
    }

    if (precision < 0)
        precision = default_precision;
    else if (type == 'r')
        type = 'g';


    buf = PyOS_double_to_string(val, (char)type, precision, flags,
                                &float_type);
    if (buf == NULL)
        goto done;
    n_digits = strlen(buf);

    if (add_pct) {


        buf[n_digits] = '%';
        n_digits += 1;
    }


    unicode_tmp = strtounicode(buf, n_digits);
    if (unicode_tmp == NULL)
        goto done;
    index = 0;


    if (PyUnicode_READ_CHAR(unicode_tmp, index) == '-') {
        sign_char = '-';
        ++index;
        --n_digits;
    }


    parse_number(unicode_tmp, index, index + n_digits, &n_remainder, &has_decimal);


    if (get_locale_info(format->type == 'n' ? LT_CURRENT_LOCALE :
                        (format->thousands_separators ?
                         LT_DEFAULT_LOCALE :
                         LT_NO_LOCALE),
                        &locale) == -1)
        goto done;


    n_total = calc_number_widths(&spec, 0, sign_char, unicode_tmp, index,
                                 index + n_digits, n_remainder, has_decimal,
                                 &locale, format, &maxchar);


    result = PyUnicode_New(n_total, maxchar);
    if (result == NULL)
        goto done;


    err = fill_number(result, 0, &spec,
                      unicode_tmp, index, index + n_digits,
                      NULL, 0,
                      format->fill_char == '\0' ? ' ' : format->fill_char,
                      &locale, 0);
    if (err)
        Py_CLEAR(result);

done:
    PyMem_Free(buf);
    Py_DECREF(unicode_tmp);
    free_locale_info(&locale);
    assert(!result || _PyUnicode_CheckConsistency(result, 1));
    return result;
}
