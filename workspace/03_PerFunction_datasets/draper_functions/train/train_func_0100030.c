mgrib_lights( LmLighting *lm, struct mgastk *astk )
{
  int i, lightsused;
  LtLight *light, **lp;
  static int prevused = 0;

  lightsused = 0;
  LM_FOR_ALL_LIGHTS(lm, i,lp) {
    light = *lp;
    ++lightsused;

    if (light->Private == 0) {

      light->Private = lightsused;
      light->changed = 1;
    }
    if (light->changed) {
      if (light->position.w == 0.0) {


	mrti(mr_comment, "Directional Light",
	     mr_lightsource, mr_distantlight, mr_int, light->Private,
	     mr_intensity, mr_float, light->intensity,
	     mr_lightcolor, mr_parray, 3, &(light->color),
	     mr_string, "from", mr_parray, 3, &(light->globalposition),
	     mr_string, "to", mr_array, 3, 0.,0.,0.,
	     mr_NULL);
      } else {

	mrti(mr_lightsource, mr_string, "pointlight", mr_int, light->Private,
	     mr_intensity, mr_float, light->intensity,
	     mr_lightcolor, mr_parray, 3, &(light->color),
	     mr_string, "from", mr_parray, 3, &(light->globalposition),
	     mr_NULL);
      }
      light->changed = 0;
    }
  }
  for (i = lightsused +1; i <= prevused; i++)
    mrti(mr_illuminate, mr_int, i, mr_int, 0, mr_NULL);
  if (prevused < lightsused) prevused = lightsused;
}
