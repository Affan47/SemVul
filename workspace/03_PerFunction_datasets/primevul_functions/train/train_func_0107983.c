int punycode_decode(
  size_t input_length,
  const char input[],
  size_t *output_length,
  punycode_uint output[])
{
  punycode_uint n, out, i, max_out, bias, oldi, w, k, digit, t;
  size_t b, j, in;


  n = initial_n;
  out = i = 0;
  max_out = *output_length > maxint ? maxint
            : (punycode_uint) *output_length;
  bias = initial_bias;


  for (b = j = 0;  j < input_length;  ++j)  if (delim(input[j])) b = j;
  if (b > max_out) return punycode_big_output;

  for (j = 0;  j < b;  ++j) {
    if (!basic(input[j])) return punycode_bad_input;
    output[out++] = input[j];
  }


  for (in = b > 0 ? b + 1 : 0;  in < input_length;  ++out) {


    for (oldi = i, w = 1, k = base;  ;  k += base) {
      if (in >= input_length) return punycode_bad_input;
      digit = decode_digit(input[in++]);
      if (digit >= base) return punycode_bad_input;
      if (digit > (maxint - i) / w) return punycode_overflow;
      i += digit * w;
      t = k <= bias  ? tmin :
          k >= bias + tmax ? tmax : k - bias;
      if (digit < t) break;
      if (w > maxint / (base - t)) return punycode_overflow;
      w *= (base - t);
    }

    bias = adapt(i - oldi, out + 1, oldi == 0);


    if (i / (out + 1) > maxint - n) return punycode_overflow;
    n += i / (out + 1);
    i %= (out + 1);


    if (out >= max_out) return punycode_big_output;

    memmove(output + i + 1, output + i, (out - i) * sizeof *output);
    output[i++] = n;
  }

  *output_length = (size_t) out;

  return punycode_success;
}
