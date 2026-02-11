ensure_writer_open(Index *self)
{
    if (!self->iw) {
        INDEX_CLOSE_READER(self);


        REF(self->analyzer);
        self->iw = iw_open(self->store, self->analyzer, false);
        self->iw->config.use_compound_file = self->config.use_compound_file;
    } else if (self->analyzer != self->iw->analyzer) {
        a_deref(self->iw->analyzer);
        REF(self->analyzer);
        self->iw->analyzer = self->analyzer;
    }
}
