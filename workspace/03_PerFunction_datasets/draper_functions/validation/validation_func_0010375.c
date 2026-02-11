client_occupies_space(ObClient *self)
{
    return !(self->type == OB_CLIENT_TYPE_DESKTOP ||
             self->type == OB_CLIENT_TYPE_SPLASH);
}
