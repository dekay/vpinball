#pragma once

/*
 * Portions of this code was derived from Mono:
 *
 * https://github.com/mono/sysdrawing-coregraphics/blob/main/System.Drawing/Graphics.cs
 */

#include "Matrix.h"
#include "GraphicsPath.h"

namespace B2S {

class Graphics {
public:
   Graphics(int x, int y);
   ~Graphics();

   void TranslateTransform(int x, int y);
   void ResetTransform();
   Matrix* GetTransform() const { return m_pModelMatrix; }
   void SetTransform(Matrix* pModelMatrix);
   void SetColor(OLE_COLOR color);
   void DrawImage(SDL_Surface* pSourceImage, SDL_Rect* pSrcRect, SDL_Rect* pDstRect);
   void DrawPath(GraphicsPath* pGraphicsPath);
   void FillPath(GraphicsPath* pPath);
   SDL_Surface* GetSurface() { return m_pSurface; }

private:
   void Initialize();
   void MoveTo(float x, float y);
   void LineTo(float x, float y);
   void PlotPath(GraphicsPath* pPath);

   int m_width;
   int m_height;
   int m_translateX;
   int m_translateY;
   B2S::Matrix* m_pModelMatrix;
   SDL_Surface* m_pSurface;
   UINT32 m_color;
   float m_cx;
   float m_cy;
};

}