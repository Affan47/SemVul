init(const Vector3& v0, const Vector3& v1, const Vector3& v2) {

    _plane = Plane(v0, v1, v2);
    _vertex[0] = v0;
    _vertex[1] = v1;
    _vertex[2] = v2;

    static int next[] = {1,2,0};

    for (int i = 0; i < 3; ++i) {
        const Vector3& e  = _vertex[next[i]] - _vertex[i];
        edgeMagnitude[i]  = e.magnitude();

        if (edgeMagnitude[i] == 0) {
            edgeDirection[i] = Vector3::zero();
        } else {
            edgeDirection[i] = e / (float)edgeMagnitude[i];
        }
    }

    _edge01 = _vertex[1] - _vertex[0];
    _edge02 = _vertex[2] - _vertex[0];

    _primaryAxis = _plane.normal().primaryAxis();
    _area = 0.5f * edgeDirection[0].cross(edgeDirection[2]).magnitude() * (edgeMagnitude[0] * edgeMagnitude[2]);

}
