pump_removexattr (call_frame_t *frame,
                  xlator_t *this,
                  loc_t *loc,
                  const char *name)
{
        afr_private_t *priv  = NULL;
	priv = this->private;
        if (!priv->use_afr_in_pump) {
                STACK_WIND (frame,
                            default_removexattr_cbk,
                            FIRST_CHILD(this),
                            FIRST_CHILD(this)->fops->removexattr,
                            loc,
                            name);
                return 0;
        }
        afr_removexattr (frame, this, loc, name);
        return 0;

}
