decrement (Time& timecode, uint32_t subframes_per_frame)
{
	Wrap wrap = NONE;

	if (timecode.negative || Timecode_IS_ZERO (timecode)) {
		timecode.negative = false;
		wrap = increment (timecode, subframes_per_frame);
		timecode.negative = true;
		return wrap;
	} else if (Timecode_IS_AROUND_ZERO (timecode) && timecode.subframes) {

		timecode.subframes = subframes_per_frame - timecode.subframes;
		timecode.negative = true;
		return SECONDS;
	}

	switch ((int)ceil (timecode.rate)) {
	case 24:
		if (timecode.frames == 0) {
			timecode.frames = 23;
			wrap = SECONDS;
		}
		break;
	case 25:
		if (timecode.frames == 0) {
			timecode.frames = 24;
			wrap = SECONDS;
		}
		break;
	case 30:
		if (timecode.drop) {
			if ((timecode.minutes % 10) && (timecode.seconds == 0)) {
				if (timecode.frames <= 2) {
					timecode.frames = 29;
					wrap = SECONDS;
				}
			} else if (timecode.frames == 0) {
				timecode.frames = 29;
				wrap = SECONDS;
			}

		} else {
			if (timecode.frames == 0) {
				timecode.frames = 29;
				wrap = SECONDS;
			}
		}
		break;
	case 60:
		if (timecode.frames == 0) {
			timecode.frames = 59;
			wrap = SECONDS;
		}
		break;
	}

	if (wrap == SECONDS) {
		if (timecode.seconds == 0) {
			timecode.seconds = 59;
			wrap = MINUTES;
			if (timecode.minutes == 0) {
				timecode.minutes = 59;
				wrap = HOURS;
				timecode.hours--;
			}
			else {
				timecode.minutes--;
			}
		} else {
			timecode.seconds--;
		}
	} else {
		timecode.frames--;
	}

	if (Timecode_IS_ZERO (timecode)) {
		timecode.negative = false;
	}

	return wrap;
}
