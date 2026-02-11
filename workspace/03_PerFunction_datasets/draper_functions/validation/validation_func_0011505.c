pd_construct(const char *_new_name)
{

  PullupResistor *pur = new PullupResistor(_new_name, "PullDown resistor", 0.0);

  pur->res->set_Vth(0);
  pur->res->set_Vpullup(0.0);
  return pur;
}
