host_is_in_net(const uschar *host, const uschar *net, int maskoffset)
{
int i;
int address[4];
int incoming[4];
int mlen;
int size = host_aton(net, address);
int insize;


if (maskoffset == 0) mlen = 99999;
  else mlen = Uatoi(net + maskoffset + 1);


insize = host_aton(host, incoming);


if (insize == 4 && incoming[0] == 0 && incoming[1] == 0 &&
    incoming[2] == 0xffff)
  {
  insize = 1;
  incoming[0] = incoming[3];
  }


if (insize != size) return FALSE;


for (i = 0; i < size; i++)
  {
  int mask;
  if (mlen == 0) mask = 0;
  else if (mlen < 32)
    {
    mask = (uint)(-1) << (32 - mlen);
    mlen = 0;
    }
  else
    {
    mask = -1;
    mlen -= 32;
    }
  if ((incoming[i] & mask) != (address[i] & mask)) return FALSE;
  }

return TRUE;
}
