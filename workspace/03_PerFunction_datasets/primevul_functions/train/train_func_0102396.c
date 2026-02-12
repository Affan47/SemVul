replace_single_character_in_place(PyStringObject *self,
                                  char from_c, char to_c,
                                  Py_ssize_t maxcount)
{
    char *self_s, *result_s, *start, *end, *next;
    Py_ssize_t self_len;
    PyStringObject *result;


    self_s = PyString_AS_STRING(self);
    self_len = PyString_GET_SIZE(self);

    next = findchar(self_s, self_len, from_c);

    if (next == NULL) {

        return return_self(self);
    }


    result = (PyStringObject *) PyString_FromStringAndSize(NULL, self_len);
    if (result == NULL)
        return NULL;
    result_s = PyString_AS_STRING(result);
    Py_MEMCPY(result_s, self_s, self_len);


    start =  result_s + (next-self_s);
    *start = to_c;
    start++;
    end = result_s + self_len;

    while (--maxcount > 0) {
        next = findchar(start, end-start, from_c);
        if (next == NULL)
            break;
        *next = to_c;
        start = next+1;
    }

    return result;
}
