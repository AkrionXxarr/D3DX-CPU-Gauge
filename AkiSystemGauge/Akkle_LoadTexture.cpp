#include "Akkle.hpp"

LPDIRECT3DTEXTURE9 Akkle::LoadTexture(wchar_t *fileName, D3DCOLOR transColor)
{
    LPDIRECT3DTEXTURE9 texture = NULL;
    D3DXIMAGE_INFO info;
    HRESULT hResult;

    hResult = D3DXGetImageInfoFromFile(fileName, &info);

    if (hResult != D3D_OK)
        return NULL;

    hResult = D3DXCreateTextureFromFileEx(
                                        m_d3dDev,
                                        fileName,
                                        info.Width,
                                        info.Height,
                                        D3DX_FROM_FILE,
                                        D3DPOOL_DEFAULT,
                                        D3DFMT_FROM_FILE,
                                        D3DPOOL_DEFAULT,
                                        D3DX_DEFAULT,
                                        D3DX_DEFAULT,
                                        0,
                                        &info,
                                        NULL,
                                        &texture
                                        );

    if (hResult != D3D_OK)
        return NULL;

    return texture;
}