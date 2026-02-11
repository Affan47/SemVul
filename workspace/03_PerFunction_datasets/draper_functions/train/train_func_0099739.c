format_small_cardinal (std::ostream& stream, uintL arg)
{
	var uintL hundreds = floor(arg,100);
	var uintL tens_and_ones = arg % 100;
	if (hundreds > 0) {
		fprint(stream,cl_format_ones[hundreds]);
		fprint(stream," hundred");
	}
	if (tens_and_ones > 0) {
		if (hundreds > 0)
			fprint(stream," and ");
		var uintL tens = floor(tens_and_ones,10);
		var uintL ones = tens_and_ones % 10;
		if (tens < 2)
			fprint(stream,cl_format_ones[tens_and_ones]);
		else {
			fprint(stream,cl_format_tens[tens]);
			if (ones > 0) {
				fprintchar(stream,'-');
				fprint(stream,cl_format_ones[ones]);
			}
		}
	}
}
