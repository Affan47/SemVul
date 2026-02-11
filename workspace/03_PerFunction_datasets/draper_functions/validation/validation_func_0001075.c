set_object_face_other(object *op) {
    sstring custom;
    int newface = 0;

    if (op->face && op->other_arch && op->other_arch->clone.face)
        newface = op->other_arch->clone.face->number;

    if (op->face != op->arch->clone.face) {

        object_set_value(op, "face_closed", op->face->name, 1);
    }

    custom = object_get_value(op, "face_opened");
    if (custom)
        newface = find_face(custom, newface);
    if (newface && op->face->number != newface) {
        op->face = &new_faces[newface];
        return TRUE;
    }
    return FALSE;
}
