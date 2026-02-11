fuzzyEq(const Matrix3& b) const {
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 3; ++c) {
            if (! G3D::fuzzyEq(elt[r][c], b[r][c])) {
                return false;
            }
        }
    }
    return true;
}
