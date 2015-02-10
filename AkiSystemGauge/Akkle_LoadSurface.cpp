#include "Akkle.hpp"

LPDIRECT3DSURFACE9 Akkle::LoadSurface(wchar_t* fileName, D3DCOLOR transColor)
{
    LPDIRECT3DSURFACE9 image = NULL;
    D3DXIMAGE_INFO info;
    HRESULT hResult;

    // Get width and height from bitmap file
    hResult = D3DXGetImageInfoFromFile(fileName, &info);
    if (hResult != D3D_OK)
        return NULL;

    // Create surface
    hResult = m_d3dDev->CreateOffscreenPlainSurface(
                                                info.Width,
                                                info.Height,
                                                D3DFMT_X8R8G8B8,
                                                D3DPOOL_DEFAULT,
                                                &image,
                                                NULL
                                                );

    if (hResult != D3D_OK)
        return NULL;

    hResult = D3DXLoadSurfaceFromFile(
                                    image,
                                    NULL,
                                    NULL,
                                    fileName,
                                    NULL,
                                    D3DX_DEFAULT,
                                    transColor,
                                    NULL
                                    );

    if (hResult != D3D_OK)
        return NULL;

    return image;
}