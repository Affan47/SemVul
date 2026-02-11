renderLaserThreat()
{
	int frame_offset, num_frames;


	num_frames = laser_warn.num_frames;

	Assert( num_frames >= 2 );

	if ( Player->threat_flags & THREAT_DUMBFIRE ) {
		if ( timestamp_elapsed(laser_warn_timer) ) {
			laser_warn_timer = timestamp(THREAT_DUMBFIRE_FLASH);
			laser_warn_frame++;
			if ( laser_warn_frame > (num_frames - 1) ) {
				laser_warn_frame = 1;
			}
		}
		frame_offset = laser_warn_frame;
	} else {
		frame_offset = 0;
	}

	renderBitmap(laser_warn.first_frame + frame_offset, position[0] + Laser_warn_offsets[0], position[1] + Laser_warn_offsets[1]);
}
