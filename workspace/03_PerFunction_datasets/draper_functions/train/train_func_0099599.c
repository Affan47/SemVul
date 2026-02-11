amitk_volume_volume_intersection_corners(const AmitkVolume * volume1,
					      const AmitkVolume * volume2,
					      AmitkCorners return_corners) {

  gint i;

  g_return_val_if_fail(AMITK_IS_VOLUME(volume1), FALSE);
  g_return_val_if_fail(AMITK_IS_VOLUME(volume2), FALSE);
  g_return_val_if_fail(AMITK_VOLUME_VALID(volume1), FALSE);
  g_return_val_if_fail(AMITK_VOLUME_VALID(volume2), FALSE);


  amitk_volume_get_enclosing_corners(volume2, AMITK_SPACE(volume1), return_corners);


  for (i=0; i<2; i++) {
    if (return_corners[i].x < 0.0) return_corners[i].x = 0;
    if (return_corners[i].y < 0.0) return_corners[i].y = 0;
    if (return_corners[i].z < 0.0) return_corners[i].z = 0;
    if (return_corners[i].x > volume1->corner.x) return_corners[i].x = volume1->corner.x;
    if (return_corners[i].y > volume1->corner.y) return_corners[i].y = volume1->corner.y;
    if (return_corners[i].z > volume1->corner.z) return_corners[i].z = volume1->corner.z;
  }

  if (REAL_EQUAL(return_corners[0].x, return_corners[1].x) ||
      REAL_EQUAL(return_corners[0].y, return_corners[1].y) ||
      REAL_EQUAL(return_corners[0].z, return_corners[1].z))
    return FALSE;
  else
    return TRUE;
}
