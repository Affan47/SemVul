GetVMTypeFromLength(unsigned int length, unsigned int size)
{

  if ( !length || length % size ) return VM::VM0;
  const unsigned int ratio = length / size;

  switch( ratio )
    {
  case 1: return VM::VM1;
  case 2: return VM::VM2;
  case 3: return VM::VM3;
  case 4: return VM::VM4;
  case 5: return VM::VM5;
  case 6: return VM::VM6;
  case 8: return VM::VM8;
  case 16: return VM::VM16;
  case 24: return VM::VM24;
  case 32: return VM::VM32;
  default:
           return VM::VM1_n;
    }
}
