#ifndef _GAUGE_HPP_
#define _GAUGE_HPP_

#include <d3d9.h>
#include <d3dx9.h>
#include <math.h>

#define ROTATION_OFFSET 225.0
#define ROTATION_MAX 270.0

#define ROTATION_STEP 35.0
#define ROTATION_DELAY 10

#define ROTATION_POW 1.5
#define ROTATION_PADDING 30.0

#define PI 3.14159265

class Gauge
{
public:
    Gauge();
    ~Gauge();

    int GetWidth() { return m_faceWidth; }
    int GetHeight() { return m_faceHeight; }

    void Offset(int xOffset, int yOffset)
    {
        m_xOffset = xOffset;
        m_yOffset = yOffset;
    }

    void SetFace(LPDIRECT3DTEXTURE9 face, int width, int height) 
    { 
        m_face = face; 
        m_faceWidth = width;
        m_faceHeight = height;
    }
    void SetNeedle(LPDIRECT3DTEXTURE9 needle, int width, int height) 
    { 
        m_needle = needle;
        m_needleWidth = width;
        m_needleHeight = height;
    }
    void SetCover(LPDIRECT3DTEXTURE9 cover, int width, int height)
    {
        m_cover = cover;
        m_coverWidth = width;
        m_coverHeight = height;
    }

    bool Clean();
    bool Draw(
            const LPDIRECT3DDEVICE9 d3dDev, 
            const LPD3DXSPRITE spriteHandler,
            const LPDIRECT3DSURFACE9 backBuffer
            );

    bool Tick(double val);
    
    LPDIRECT3DTEXTURE9 GetFace() { return m_face; }
    LPDIRECT3DTEXTURE9 GetNeedle() { return m_needle; }
    LPDIRECT3DTEXTURE9 GetCover() { return m_cover; }

private:
    int m_xOffset, m_yOffset;

    int m_faceWidth, m_faceHeight;
    int m_needleWidth, m_needleHeight;
    int m_coverWidth, m_coverHeight;

    double m_rotOffset;
    double m_rotMax; // + m_rotOffset

    double m_needleProjRot;
    double m_needleLastProjRot;
    double m_needleCurRot;
    double m_needleLastRot;

    double m_rotateStep;
    double m_needleStep;

    double m_curDelta;
    double m_lastDelta;

    double m_rotPow;
    double m_rotPadding;

    unsigned int m_lastTick;
    unsigned int m_tickRotDelay;
    unsigned int m_curRotDelay;

    LPDIRECT3DTEXTURE9 m_face;
    LPDIRECT3DTEXTURE9 m_needle;
    LPDIRECT3DTEXTURE9 m_cover;
};

#endif