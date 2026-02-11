_kmalloc(unsigned int size, int align, unsigned int* phys) {

  if(!size) {
    return NULL;
  }


  if(placement == 0) {
    placement = (unsigned int)&_kernel_end;
  }


  if(align == 1 && ((placement) & 0x0fff)) {
    placement &= 0xfffff000;
    placement += 0x1000;
  }

  if(phys) {
    *phys = placement;
  }

  unsigned int tmp = placement;
  placement += size;
  return (void*) tmp;
}
