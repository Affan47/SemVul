start_gethit_animation(enemy * ThisRobot)
{


	if ((last_gethit_animation_image[Druidmap[ThisRobot->type].individual_shape_nr] - first_gethit_animation_image[Druidmap[ThisRobot->type].individual_shape_nr] > 0)) {
		if ((ThisRobot->animation_type == DEATH_ANIMATION)) {
			DebugPrintf(-4, "\n%s(): WARNING: animation phase reset for INFOUT bot... ", __FUNCTION__);
		}
		ThisRobot->animation_phase = ((float)first_gethit_animation_image[Druidmap[ThisRobot->type].individual_shape_nr]) + 0.1;
		ThisRobot->animation_type = GETHIT_ANIMATION;
	}

}
