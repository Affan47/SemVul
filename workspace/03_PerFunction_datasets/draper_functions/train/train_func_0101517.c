g3d_quat_to_rotation_xyz(G3DQuat *q, G3DFloat *rx, G3DFloat *ry,
	G3DFloat *rz)
{
	G3DFloat t;


	t = 1 - 2 * (q[1] * q[1] + q[2] * q[2]);
	if(t != 0)
		*rx = atan(2 * (q[0] * q[1] + q[2] * q[3]) / t);
	else
		*rx = 0.0;


	*ry = asin(2 * (q[0] * q[2] - q[1] * q[3]));


	t = 1 - 2 * (q[2] * q[2] + q[3] * q[3]);
	if(t != 0)
		*rz = atan(2 * (q[0] * q[3] + q[1] * q[2]) / t);
	else
		*rz = 0.0;

	return TRUE;
}
