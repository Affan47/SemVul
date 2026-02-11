unpack_exchange(int nlocal, double *buf)
{
  int m = 0;
  int flag = shake_flag[nlocal] = static_cast<int> (buf[m++]);
  if (flag == 1) {
    shake_atom[nlocal][0] = static_cast<int> (buf[m++]);
    shake_atom[nlocal][1] = static_cast<int> (buf[m++]);
    shake_atom[nlocal][2] = static_cast<int> (buf[m++]);
    shake_type[nlocal][0] = static_cast<int> (buf[m++]);
    shake_type[nlocal][1] = static_cast<int> (buf[m++]);
    shake_type[nlocal][2] = static_cast<int> (buf[m++]);
  } else if (flag == 2) {
    shake_atom[nlocal][0] = static_cast<int> (buf[m++]);
    shake_atom[nlocal][1] = static_cast<int> (buf[m++]);
    shake_type[nlocal][0] = static_cast<int> (buf[m++]);
  } else if (flag == 3) {
    shake_atom[nlocal][0] = static_cast<int> (buf[m++]);
    shake_atom[nlocal][1] = static_cast<int> (buf[m++]);
    shake_atom[nlocal][2] = static_cast<int> (buf[m++]);
    shake_type[nlocal][0] = static_cast<int> (buf[m++]);
    shake_type[nlocal][1] = static_cast<int> (buf[m++]);
  } else if (flag == 4) {
    shake_atom[nlocal][0] = static_cast<int> (buf[m++]);
    shake_atom[nlocal][1] = static_cast<int> (buf[m++]);
    shake_atom[nlocal][2] = static_cast<int> (buf[m++]);
    shake_atom[nlocal][3] = static_cast<int> (buf[m++]);
    shake_type[nlocal][0] = static_cast<int> (buf[m++]);
    shake_type[nlocal][1] = static_cast<int> (buf[m++]);
    shake_type[nlocal][2] = static_cast<int> (buf[m++]);
  }
  return m;
}
