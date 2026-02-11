checkDimen(const imageStruct&img) {
      return (
              (img.xsize == m_width ) &&
              (img.ysize == m_height) &&
              (csize2depth       (img.csize     ) == m_depth ) &&
              (updown2orientation(img.upsidedown) == m_orientation)
              );
    }
