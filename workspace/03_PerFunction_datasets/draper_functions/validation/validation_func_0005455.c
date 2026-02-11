HTS_Vocoder_get_excitation(HTS_Vocoder * v, const double *lpf)
{
   double x;
   double noise, pulse = 0.0;

   if (v->excite_buff_size > 0) {
      noise = HTS_white_noise(v);
      pulse = 0.0;
      if (v->pitch_of_curr_point == 0.0) {
         HTS_Vocoder_excite_unvoiced_frame(v, noise);
      } else {
         v->pitch_counter += 1.0;
         if (v->pitch_counter >= v->pitch_of_curr_point) {
            pulse = sqrt(v->pitch_of_curr_point);
            v->pitch_counter -= v->pitch_of_curr_point;
         }
         HTS_Vocoder_excite_voiced_frame(v, noise, pulse, lpf);
         v->pitch_of_curr_point += v->pitch_inc_per_point;
      }
      x = v->excite_ring_buff[v->excite_buff_index];
      v->excite_ring_buff[v->excite_buff_index] = 0.0;
      v->excite_buff_index++;
      if (v->excite_buff_index >= v->excite_buff_size)
         v->excite_buff_index = 0;
   } else {
      if (v->pitch_of_curr_point == 0.0) {
         x = HTS_white_noise(v);
      } else {
         v->pitch_counter += 1.0;
         if (v->pitch_counter >= v->pitch_of_curr_point) {
            x = sqrt(v->pitch_of_curr_point);
            v->pitch_counter -= v->pitch_of_curr_point;
         } else {
            x = 0.0;
         }
         v->pitch_of_curr_point += v->pitch_inc_per_point;
      }
   }

   return x;
}
