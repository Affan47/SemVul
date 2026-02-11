wvariance (GPtrArray * array, guint num_elements, gdouble wmean)
{
  analysis_element_t * element;
  gdouble wsumofsquares = 0 ;
  gdouble Wa = 0;
  gdouble Wb = 0;
  gdouble wi;
  gdouble delta;
  gdouble factor;
  guint i;

  if (num_elements < 2) return NAN;


  for (i = 0; i < num_elements; i++) {
    element = g_ptr_array_index(array, i);
    wi = element->weight;

    if (wi > 0) {
      delta = element->value-wmean;
      Wa += wi ;
      Wb += wi*wi;
      wsumofsquares += (delta * delta - wsumofsquares) * (wi / Wa);
    }
  }

  factor = (Wa*Wa)/((Wa*Wa)-Wb);

  return factor*wsumofsquares;
}
