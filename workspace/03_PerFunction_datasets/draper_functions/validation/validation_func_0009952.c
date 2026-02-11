pow(const vvp_vector2_t&x, vvp_vector2_t&y)
{

      if (y == vvp_vector2_t(0L, 1)) {
	    return vvp_vector2_t(1L, 1);
      }


      if (y.value(0) == 1) {
	    y.set_bit(0, 0);
	    vvp_vector2_t res = x * pow(x, y);
	    res.trim();
	    return res;
      }

      y >>= 1;
      vvp_vector2_t z = pow(x, y);
      vvp_vector2_t res = z * z;
      res.trim();
      return res;
}
