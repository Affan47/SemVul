input(SMInput input)
{
	switch (d->policy_) {
		case PreferencesPolicy:


			if (SMI_CANCEL == input || SMI_HIDE == input) {
				if (d->state_ != APPLIED)
					d->state_ = INITIAL;
			} else {
				d->nextState(input);
			}
			break;
		case IgnorantPolicy:
			break;
		default:

			if (SMI_CANCEL == input || SMI_HIDE == input) {
				if (d->state_ == AUTOAPPLY_INITIAL
					  || d->state_ == AUTOAPPLY_CHANGED)
					d->state_ = AUTOAPPLY_INITIAL;
				else
					d->state_ = INITIAL;
			} else
				d->nextState(input);
			break;
	}
}
