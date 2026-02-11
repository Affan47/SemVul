GMT_init_ellipsoid (void)
{
	double f;


	f = gmtdefs.ref_ellipsoid[gmtdefs.ellipsoid].flattening;
	project_info.ECC2 = 2.0 * f - f * f;
	project_info.ECC4 = project_info.ECC2 * project_info.ECC2;
	project_info.ECC6 = project_info.ECC2 * project_info.ECC4;
	project_info.one_m_ECC2 = 1.0 - project_info.ECC2;
	project_info.i_one_m_ECC2 = 1.0 / project_info.one_m_ECC2;
	project_info.ECC = d_sqrt (project_info.ECC2);
	project_info.half_ECC = 0.5 * project_info.ECC;
	project_info.i_half_ECC = 0.5 / project_info.ECC;
	project_info.EQ_RAD = gmtdefs.ref_ellipsoid[gmtdefs.ellipsoid].eq_radius;
	project_info.i_EQ_RAD = 1.0 / project_info.EQ_RAD;


	project_info.DIST_M_PR_DEG = project_info.M_PR_DEG = TWO_PI * GMT_mean_radius (project_info.EQ_RAD, f) / 360.0;
	project_info.DIST_KM_PR_DEG = project_info.KM_PR_DEG = 0.001 * project_info.M_PR_DEG;
}
