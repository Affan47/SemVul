us_webapp_director_add_app( us_webapp_director_t *self, us_webapp_t *app )
{
    bool r = false;
    if ( app )
    {
        if ( self->m_last_app )
        {
            self->m_last_app->m_next = app;
            self->m_last_app = app;
        }
        else
        {
            self->m_apps = app;
            self->m_last_app = app;
        }
        r = true;
    }
    return r;
}
