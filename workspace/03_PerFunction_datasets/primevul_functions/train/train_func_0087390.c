writeDataTpduHeader(CotpConnection* self, int isLastUnit)
{

    uint8_t* buffer = self->writeBuffer->buffer;

    buffer[4] = 0x02;
    buffer[5] = 0xf0;
    if (isLastUnit)
        buffer[6] = 0x80;
    else
        buffer[6] = 0x00;

    self->writeBuffer->size = 7;
}
