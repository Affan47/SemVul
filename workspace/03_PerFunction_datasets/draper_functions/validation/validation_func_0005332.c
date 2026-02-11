directionSymbol(direction_type dir) {
  char c='?';
  int cnt=0;
  char symbols[] = ">\\v/<\\^/";

  if(dir == 0) return '.';

  dir = findDominant(dir);

  for(int i=0; i<8; i++) {
	if(dir & (1<<i)) {
	  cnt++;
	  c = symbols[i];
	}
  }
  if(cnt>1) c = 'X';

  switch(dir) {
  case 1+16:
  case 128+1+2+8+16+32:
	c = '-';
	break;
  case 1+2+8+16+32:
  case 128+1+8+16+32:
	c = '<';
	break;
  case 128+1+2+16+32:
  case 128+1+2+8+16:
	c = '>';
	break;
  case 4+64:
  case 2+4+8+32+64+128:
	c = '|';
	break;
  case 4+8+32+64+128:
  case 2+4+32+64+128:
	c = '^';
	break;
  case 2+4+8+64+128:
  case 2+4+8+32+64:
	c = 'v';
	break;
  case 255:
	c = '*';
	break;
  default:
	break;
  }
  return c;
}
