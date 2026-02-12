string PacketReader::getText(bool multi)
{
  string ret;
  ret.reserve(40);
  while(d_pos < d_startrecordpos + d_recordlen ) {
    if(!ret.empty()) {
      ret.append(1,' ');
    }
    unsigned char labellen=d_content.at(d_pos++);

    ret.append(1,'"');
    if(labellen) {
      string val(&d_content.at(d_pos), &d_content.at(d_pos+labellen-1)+1);
      ret.append(txtEscape(val));
    }
    ret.append(1,'"');
    d_pos+=labellen;
    if(!multi)
      break;
  }

  return ret;
}
