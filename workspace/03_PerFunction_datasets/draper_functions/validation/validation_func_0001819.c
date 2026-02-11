ibus_sunpinyin_engine_destroy(IBusEngine *py_engine)
{

    delete GET_PY_ENGINE(py_engine);
    GET_PY_ENGINE(py_engine) = NULL;
    IBUS_OBJECT_CLASS (parent_class)->destroy( IBUS_OBJECT(py_engine));
}
