get_message_buffer(ScmUVector *v, u_int *size)
{
    if (SCM_UVECTOR_IMMUTABLE_P(v)) {
        Scm_Error("attempted to use an immutable uniform vector as a buffer");
    }
    *size = Scm_UVectorSizeInBytes(v);
    return (char *)SCM_UVECTOR_ELEMENTS(v);
}
