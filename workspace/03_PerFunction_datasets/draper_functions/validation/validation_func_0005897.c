THTensor_zero(THTensor *tensor)
{
  TH_TENSOR_APPLY(double, tensor, *tensor_p = 0;);
}
