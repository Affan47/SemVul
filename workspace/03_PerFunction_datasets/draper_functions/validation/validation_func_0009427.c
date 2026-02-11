simple_it_next(song_iterator_t *_self, unsigned char *buf, int *result)
{
	struct simple_it_struct *self = (struct simple_it_struct *) _self;

	if (self->lifetime_remaining == -1) {
		error("Song iterator called post mortem");
		return SI_FINISHED;
	}

	if (self->lifetime_remaining) {

		if (self->cue_counter < self->cues_nr) {
			int time_to_cue = self->cues[self->cue_counter];

			if (self->cue_progress == time_to_cue) {
				++self->cue_counter;
				self->cue_progress = 0;
				*result = self->cue_counter;
				return SI_ABSOLUTE_CUE;
			} else {
				int retval = time_to_cue - self->cue_progress;
				self->cue_progress = time_to_cue;

				if (retval > self->lifetime_remaining) {
					retval = self->lifetime_remaining;
					self->lifetime_remaining = 0;
					self->cue_progress = retval;
					return retval;
				}

				self->lifetime_remaining -= retval;
				return retval;
			}
		} else {
			int retval = self->lifetime_remaining;
			self->lifetime_remaining = 0;
			return retval;
		}

	} else {
		self->lifetime_remaining = -1;
		return SI_FINISHED;
	}
}
