eval(SeVec3d& result) const
{
    SeVec3d a;
    const SeExprNode* child0 = child(0);
    child0->eval(a);
    result[0] = !a[0];
    if (_isVec) {
	result[1] = !a[1];
	result[2] = !a[2];
    }
}
