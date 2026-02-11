spif_obj_set_class(spif_obj_t self, spif_class_t cls)
{
    ASSERT_RVAL(!SPIF_OBJ_ISNULL(self), FALSE);
    self->cls = cls;
    return TRUE;
}
