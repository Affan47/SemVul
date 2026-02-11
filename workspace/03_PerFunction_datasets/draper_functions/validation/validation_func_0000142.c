PySys_ResetWarnOptions(void)
{
    if (warnoptions == NULL || !PyList_Check(warnoptions))
        return;
    PyList_SetSlice(warnoptions, 0, PyList_GET_SIZE(warnoptions), NULL);
}
