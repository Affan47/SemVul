view_orbit_y(GF_Compositor *compositor, GF_Camera *cam, Fixed dy)
{
	GF_Matrix mx;
	SFVec3f axis;
	if (!dy) return;
	axis = camera_get_right_dir(cam);
	gf_mx_rotation_matrix(&mx, cam->target, axis, dy);
	gf_mx_apply_vec(&mx, &cam->position);

	cam->up = gf_vec_cross(camera_get_pos_dir(cam), axis);
	gf_vec_norm(&cam->up);
	camera_changed(compositor, cam);
}
