relay_websocket_decode_frame (const unsigned char *buffer,
                              unsigned long long buffer_length,
                              unsigned char *decoded,
                              unsigned long long *decoded_length)
{
    unsigned long long i, index_buffer, length_frame_size, length_frame;
    unsigned char opcode;

    *decoded_length = 0;
    index_buffer = 0;


    while (index_buffer + 1 < buffer_length)
    {
        opcode = buffer[index_buffer] & 15;


        if (!(buffer[index_buffer + 1] & 128))
            return 0;


        length_frame_size = 1;
        length_frame = buffer[index_buffer + 1] & 127;
        index_buffer += 2;
        if (index_buffer >= buffer_length)
            return 0;
        if ((length_frame == 126) || (length_frame == 127))
        {
            length_frame_size = (length_frame == 126) ? 2 : 8;
            if (index_buffer + length_frame_size > buffer_length)
                return 0;
            length_frame = 0;
            for (i = 0; i < length_frame_size; i++)
            {
                length_frame += (unsigned long long)buffer[index_buffer + i] << ((length_frame_size - i - 1) * 8);
            }
            index_buffer += length_frame_size;
        }


        if (index_buffer + 4 > buffer_length)
            return 0;
        int masks[4];
        for (i = 0; i < 4; i++)
        {
            masks[i] = (int)((unsigned char)buffer[index_buffer + i]);
        }
        index_buffer += 4;


        switch (opcode)
        {
            case WEBSOCKET_FRAME_OPCODE_PING:
                decoded[*decoded_length] = RELAY_CLIENT_MSG_PING;
                break;
            case WEBSOCKET_FRAME_OPCODE_CLOSE:
                decoded[*decoded_length] = RELAY_CLIENT_MSG_CLOSE;
                break;
            default:
                decoded[*decoded_length] = RELAY_CLIENT_MSG_STANDARD;
                break;
        }
        *decoded_length += 1;


        if ((length_frame > buffer_length)
            || (index_buffer + length_frame > buffer_length))
        {
            return 0;
        }
        for (i = 0; i < length_frame; i++)
        {
            decoded[*decoded_length + i] = (int)((unsigned char)buffer[index_buffer + i]) ^ masks[i % 4];
        }
        decoded[*decoded_length + length_frame] = '\0';
        *decoded_length += length_frame + 1;
        index_buffer += length_frame;
    }

    return 1;
}
