void eflush(void) {

   if (current_output_stream != NULL)
      fflush(current_output_stream);
}
