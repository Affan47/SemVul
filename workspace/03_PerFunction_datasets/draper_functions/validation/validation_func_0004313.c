operator- (const cl_N& x, const cl_N& y)
{


	if (realp(x)) {
		DeclareType(cl_R,x);
		if (realp(y)) {
			DeclareType(cl_R,y);
			return x-y;
		} else {
			DeclareType(cl_C,y);

			var const cl_R& a = x;
			var const cl_R& b = realpart(y);
			var const cl_R& c = imagpart(y);
			return complex_C(a-b,-c);
		}
	} else {
		DeclareType(cl_C,x);
		if (realp(y)) {
			DeclareType(cl_R,y);

			var const cl_R& a = realpart(x);
			var const cl_R& b = imagpart(x);
			var const cl_R& c = y;
			return complex_C(a-c,b);
		} else {
			DeclareType(cl_C,y);

			var const cl_R& a = realpart(x);
			var const cl_R& b = imagpart(x);
			var const cl_R& c = realpart(y);
			var const cl_R& d = imagpart(y);
			return complex(a-c,b-d);
		}
	}
}
