drawOutlinesHtl()
{
	matrix base_tilt = vmd_identity_matrix;
	vec3d base_tilt_norm;

	if ((xy_plane == -1) || (xz_yz_plane == -1))
		return;

	g3_start_instance_matrix(&vmd_zero_vector, &vmd_identity_matrix, true);


		vm_angle_2_matrix(&base_tilt, PI/6, 0);
		vm_vec_rotate(&base_tilt_norm, &vmd_y_vector, &base_tilt);

		gr_set_bitmap(xy_plane, GR_ALPHABLEND_FILTER, GR_BITBLT_MODE_NORMAL, 1.0f);
		g3_draw_polygon(&vmd_zero_vector, &base_tilt_norm, scale, scale, TMAP_FLAG_TEXTURED | TMAP_HTL_3D_UNLIT);

		gr_set_bitmap(xz_yz_plane, GR_ALPHABLEND_FILTER, GR_BITBLT_MODE_NORMAL, 1.0f);

		g3_draw_polygon(&vmd_zero_vector, &vmd_x_vector, scale, scale, TMAP_FLAG_TEXTURED | TMAP_HTL_3D_UNLIT);
		g3_draw_polygon(&vmd_zero_vector, &vmd_z_vector, scale, scale, TMAP_FLAG_TEXTURED | TMAP_HTL_3D_UNLIT);
	g3_done_instance(true);
}
