#include "Gauge.hpp"

bool Gauge::Draw(
               const LPDIRECT3DDEVICE9 d3dDev, 
               const LPD3DXSPRITE spriteHandler,
               const LPDIRECT3DSURFACE9 backBuffer)
{
    D3DXVECTOR3 faceOffset(0, 0, 0);
    D3DXVECTOR3 needleOffset(0, 0, 0);
    D3DXVECTOR3 coverOffset(0, 0, 0);
    D3DXVECTOR2 rotationOffset(0, 0);

    D3DXMATRIX faceMatrix;
    D3DXMATRIX needleMatrix;
    D3DXMATRIX coverMatrix;

    // Draw face
    faceOffset.x = static_cast<float>(m_xOffset);
    faceOffset.y = static_cast<float>(m_yOffset);

    D3DXMatrixTransformation2D(
                            &faceMatrix,
                            NULL,
                            0.0f,
                            NULL,
                            NULL,
                            0,
                            NULL
                            );

    spriteHandler->SetTransform(&faceMatrix);

    spriteHandler->Draw(
                    m_face,
                    NULL,
                    NULL,
                    &faceOffset,
                    D3DCOLOR_XRGB(255, 255, 255)
                    );

    // Draw needle
    needleOffset.x = static_cast<float>((m_faceWidth / 2.0) - (m_needleWidth / 2.0));
    needleOffset.y = static_cast<float>((m_faceHeight / 2.0) - (m_needleHeight / 2.0));

    needleOffset += faceOffset;

    rotationOffset.x = static_cast<float>(faceOffset.x + (m_faceWidth / 2.0));
    rotationOffset.y = static_cast<float>(faceOffset.y + (m_faceHeight / 2.0));

    if (true)
    {
        m_lastTick = GetTickCount();

        double rotateDelta = m_needleProjRot - m_needleCurRot;
        double absDelta = max(abs(rotateDelta), 1.0);

        m_needleCurRot += (rotateDelta / (ROTATION_STEP + pow(m_rotPadding + 1, ROTATION_POW)));

        if (m_rotPadding > 0)
            m_rotPadding -= .5;
    }


    D3DXMatrixTransformation2D(
                            &needleMatrix,
                            NULL,
                            0.0f,
                            NULL,
                            &rotationOffset,
                            static_cast<float>(m_needleCurRot * (PI / 180)),
                            NULL
                            );

    spriteHandler->SetTransform(&needleMatrix);

    spriteHandler->Draw(
                    m_needle,
                    NULL,
                    NULL,
                    &needleOffset,
                    D3DCOLOR_XRGB(255, 255, 255)
                    );

    // Draw cover
    coverOffset.x = static_cast<float>((m_faceWidth / 2.0) - (m_needleWidth / 2.0));
    coverOffset.y = static_cast<float>((m_faceHeight / 2.0) - (m_needleHeight / 2.0));

    coverOffset += faceOffset;

    D3DXMatrixTransformation2D(
                            &coverMatrix,
                            NULL,
                            0.0f,
                            NULL,
                            NULL,
                            0,
                            NULL
                            );

    spriteHandler->SetTransform(&coverMatrix);

    spriteHandler->Draw(
                    m_cover,
                    NULL,
                    NULL,
                    &coverOffset,
                    D3DCOLOR_XRGB(255, 255, 255)
                    );

    return true;
}