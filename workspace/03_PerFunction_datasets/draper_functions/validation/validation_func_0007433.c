ce_string_toupper_inrange(CeString *self, CeInt begin, CeInt end)
{
        CE_STRING_INITIAL();

        CE_RANGE_INITIAL(begin, end, self->len);

        CeInt i = begin;

        for (; i <= end; i++) {
                _self->data[i] = toupper( _self->data[i] );
        }

        return self;
}
