p3m_find_error(double alphaL, int mesh, int cao, int method) {
    int *mesh_id, *cao_id;


    mesh_id = bsearch(&mesh, meshes, n_meshes, sizeof(int), compare_ints);
    cao_id =  bsearch(&cao, caos, n_caos, sizeof(int), compare_ints);


    if((mesh_id == NULL) || (cao_id == NULL) || (alphaL > alphaLmax))
      return -1.;
    else
      switch(method) {
      case 0:
	return p3m_find_q_ik(alphaL, mesh_id - meshes, cao_id - caos);
      case 1:
	return p3m_find_q_ik_i(alphaL, mesh_id - meshes, cao_id - caos);
      case 2:
	return p3m_find_q_ad(alphaL, mesh_id - meshes, cao_id - caos);
      case 3:
	return p3m_find_q_ad_i(alphaL, mesh_id - meshes, cao_id - caos);
      default:
	return -1;
      }
}
