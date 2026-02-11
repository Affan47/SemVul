json_input_read_byte(JSONInputReader *reader)
{
        int result;
        int err;


        if (reader->input_buffer_pos >= reader->input_buffer_len) {


                if (reader->eof) {
                        return JSON_ERROR_END_OF_FILE;
                }

                err = json_input_buffer_fill(reader);

                if (err < 0) {
                        return err;
                }

                reader->input_buffer_pos = 0;
        }


        if (json_input_is_eof(reader)) {
                return JSON_ERROR_END_OF_FILE;
        }


        result = reader->input_buffer[reader->input_buffer_pos];
        ++reader->input_buffer_pos;

        return result;
}
