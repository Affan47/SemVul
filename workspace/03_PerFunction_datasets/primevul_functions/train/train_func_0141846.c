PyImaging_DecoderNew(int contextsize)
{
    ImagingDecoderObject *decoder;
    void *context;

    if(PyType_Ready(&ImagingDecoderType) < 0)
        return NULL;

    decoder = PyObject_New(ImagingDecoderObject, &ImagingDecoderType);
    if (decoder == NULL)
        return NULL;


    memset(&decoder->state, 0, sizeof(decoder->state));


    if (contextsize > 0) {
        context = (void*) calloc(1, contextsize);
        if (!context) {
            Py_DECREF(decoder);
            (void) PyErr_NoMemory();
            return NULL;
        }
    } else
        context = 0;


    decoder->state.context = context;


    decoder->lock = NULL;
    decoder->im = NULL;


    decoder->cleanup = NULL;

    return decoder;
}
