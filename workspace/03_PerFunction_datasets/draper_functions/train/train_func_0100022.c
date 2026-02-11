getAdjustmentFromTextureTarget(unsigned TextureType, bool hasLOD,
                                      unsigned SrcSelect[4], unsigned CT[4],
                                      bool &useShadowVariant) {
    enum TextureTypes {
      TEXTURE_1D = 1,
      TEXTURE_2D,
      TEXTURE_3D,
      TEXTURE_CUBE,
      TEXTURE_RECT,
      TEXTURE_SHADOW1D,
      TEXTURE_SHADOW2D,
      TEXTURE_SHADOWRECT,
      TEXTURE_1D_ARRAY,
      TEXTURE_2D_ARRAY,
      TEXTURE_SHADOW1D_ARRAY,
      TEXTURE_SHADOW2D_ARRAY,
      TEXTURE_SHADOWCUBE,
      TEXTURE_2D_MSAA,
      TEXTURE_2D_ARRAY_MSAA,
      TEXTURE_CUBE_ARRAY,
      TEXTURE_SHADOWCUBE_ARRAY
    };

    switch (TextureType) {
    case 0:
      useShadowVariant = false;
      return;
    case TEXTURE_RECT:
    case TEXTURE_1D:
    case TEXTURE_2D:
    case TEXTURE_3D:
    case TEXTURE_CUBE:
    case TEXTURE_1D_ARRAY:
    case TEXTURE_2D_ARRAY:
    case TEXTURE_CUBE_ARRAY:
    case TEXTURE_2D_MSAA:
    case TEXTURE_2D_ARRAY_MSAA:
      useShadowVariant = false;
      break;
    case TEXTURE_SHADOW1D:
    case TEXTURE_SHADOW2D:
    case TEXTURE_SHADOWRECT:
    case TEXTURE_SHADOW1D_ARRAY:
    case TEXTURE_SHADOW2D_ARRAY:
    case TEXTURE_SHADOWCUBE:
    case TEXTURE_SHADOWCUBE_ARRAY:
      useShadowVariant = true;
      break;
    default:
      llvm_unreachable("Unknow Texture Type");
    }

    if (TextureType == TEXTURE_RECT ||
        TextureType == TEXTURE_SHADOWRECT) {
      CT[0] = 0;
      CT[1] = 0;
    }

    if (TextureType == TEXTURE_CUBE_ARRAY ||
        TextureType == TEXTURE_SHADOWCUBE_ARRAY)
      CT[2] = 0;

    if (TextureType == TEXTURE_1D_ARRAY ||
        TextureType == TEXTURE_SHADOW1D_ARRAY) {
      if (hasLOD && useShadowVariant) {
        CT[1] = 0;
      } else {
        CT[2] = 0;
        SrcSelect[2] = 1;
      }
    } else if (TextureType == TEXTURE_2D_ARRAY ||
        TextureType == TEXTURE_SHADOW2D_ARRAY) {
      CT[2] = 0;
    }

    if ((TextureType == TEXTURE_SHADOW1D ||
        TextureType == TEXTURE_SHADOW2D ||
        TextureType == TEXTURE_SHADOWRECT ||
        TextureType == TEXTURE_SHADOW1D_ARRAY) &&
        !(hasLOD && useShadowVariant))
      SrcSelect[3] = 2;
  }
