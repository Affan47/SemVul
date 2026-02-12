lzw_decoder_feed (LZWDecoder *self,
                  guint8     *input,
                  gsize       input_length,
                  guint8     *output,
                  gsize       output_length)
{
        gsize i, n_written = 0;

        g_return_val_if_fail (LZW_IS_DECODER (self), 0);


        if (self->last_code == self->eoi_code)
                return 0;


        for (i = 0; i < input_length; i++) {
                guint8 d = input[i];
                int n_available;


                for (n_available = 8; n_available > 0; ) {
                        int n_bits, new_bits;


                        n_bits = MIN (self->code_size - self->code_bits, n_available);
                        new_bits = d & ((1 << n_bits) - 1);
                        d = d >> n_bits;
                        n_available -= n_bits;


                        self->code = new_bits << self->code_bits | self->code;
                        self->code_bits += n_bits;
                        if (self->code_bits < self->code_size)
                                continue;


                        if (self->code == self->eoi_code) {
                                self->last_code = self->code;
                                return n_written;
                        }


                        if (self->code == self->clear_code) {
                                self->code_table_size = self->eoi_code + 1;
                                self->code_size = self->min_code_size;
                        } else {


                                if (self->last_code != self->clear_code && self->code_table_size < MAX_CODES) {
                                        if (self->code < self->code_table_size)
                                                add_code (self, self->code);
                                        else if (self->code == self->code_table_size)
                                                add_code (self, self->last_code);
                                        else {

                                                self->last_code = self->eoi_code;
                                                return output_length;
                                        }


                                        if (self->code_table_size == (1 << self->code_size) && self->code_size < LZW_CODE_MAX)
                                                self->code_size++;
                                }


                                n_written += write_indexes (self, output + n_written, output_length - n_written);
                        }

                        self->last_code = self->code;
                        self->code = 0;
                        self->code_bits = 0;


                        if (n_written >= output_length)
                                return output_length;
                }
        }

        return n_written;
}
