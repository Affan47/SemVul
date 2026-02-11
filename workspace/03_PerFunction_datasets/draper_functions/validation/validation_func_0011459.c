pull(int port)
{
  Packet *p = input(port).pull();
  if (p) {
    bool ewma = ((unsigned) ((click_random() >> 5) & 0xffff) <= _ratio);
    _lock->acquire();
    update_rates(p, port == 0, ewma);
    _lock->release();
  }
  return p;
}
