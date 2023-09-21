/*
 * Portions of this code was derived from Mono:
 *
 * https://github.com/mono/sysdrawing-coregraphics/blob/main/System.Drawing/Graphics.cs
 */

#include "stdafx.h"

#include "Graphics.h"

namespace B2S {

Graphics::Graphics(int x, int y)
{
   m_width = x;
   m_height = y;
   m_translateX = 0;
   m_translateY = 0;
   m_color = RGB(0, 0, 0);

   Initialize();
}

Graphics::~Graphics()
{
   delete m_pModelMatrix;

   if (m_pSurface)
      SDL_FreeSurface(m_pSurface);
}

void Graphics::Initialize()
{
   m_pModelMatrix = new Matrix();
   m_pSurface = SDL_CreateRGBSurfaceWithFormat(0, m_width, m_height, 32, SDL_PIXELFORMAT_RGBA32);
}

void Graphics::TranslateTransform(int x, int y)
{
   m_translateX += x;
   m_translateY += y;
}

void Graphics::ResetTransform()
{
   m_pModelMatrix->Reset();
}

void Graphics::SetTransform(Matrix* pModelMatrix)
{
   delete m_pModelMatrix;

   m_pModelMatrix = pModelMatrix->Clone();
}

void Graphics::SetColor(OLE_COLOR color)
{
   m_color = SDL_MapRGBA(m_pSurface->format, GetRValue(color), GetGValue(color), GetBValue(color), 0xFF);
}

void Graphics::DrawImage(SDL_Surface* pSourceImage, SDL_Rect* pSrcRect, SDL_Rect* pDstRect)
{
   SDL_BlitScaled(pSourceImage, pSrcRect, m_pSurface, pDstRect);
}

void Graphics::DrawPath(GraphicsPath* pGraphicsPath)
{
   SDL_LockSurface(m_pSurface);

   PlotPath(pGraphicsPath);

   SDL_UnlockSurface(m_pSurface);
}

void Graphics::FillPath(GraphicsPath* pGraphicsPath)
{
   DrawPath(pGraphicsPath);
}

void Graphics::MoveTo(float x, float y)
{
   if (m_pModelMatrix)
      m_pModelMatrix->TransformPoint(x, y);

   m_cx = x + m_translateX;
   m_cy = y + m_translateY;
}

void Graphics::LineTo(float x, float y)
{
   if (m_pModelMatrix)
      m_pModelMatrix->TransformPoint(x, y);

   x += m_translateX;
   y += m_translateY;

   int dx = abs(round(x) - round(m_cx));
   int dy = abs(round(y) - round(m_cy));
   int sx = m_cx < x ? 1 : -1;
   int sy = m_cy < y ? 1 : -1;
   int err = dx - dy;

   int x0 = round(m_cx);
   int y0 = round(m_cy);

   UINT32* pPixels = (UINT32*)m_pSurface->pixels;

   while ((x0 != round(x) || y0 != round(y)) && (x0 >= 0 && y0 >= 0 && x0 < m_pSurface->w && y0 < m_pSurface->h)) {
      pPixels[(y0 * m_pSurface->w) + x0] = m_color;

      int e2 = err * 2;
      if (e2 > -dy) {
         err -= dy;
         x0 += sx;
      }
      if (e2 < dx) {
         err += dx;
         y0 += sy;
      }
   }
}

void Graphics::PlotPath(GraphicsPath* pPath)
{
   float x1 = 0;
   float y1 = 0;
   float x2 = 0;
   float y2 = 0;
   float x3 = 0;
   float y3 = 0;

   vector<SDL_FPoint> points = pPath->GetPoints();
   vector<PathPointType> types = pPath->GetTypes();
   int bidx = 0;

   UINT32* pPixels = (UINT32*)m_pSurface->pixels;

   for (int i = 0; i < points.size(); i++) {
      SDL_FPoint point = points[i];
      PathPointType type = types[i];

      switch (type & PathPointType_PathTypeMask) {
         case PathPointType_Start:
            MoveTo(point.x, point.y);
            break;

         case PathPointType_Line:
            LineTo(point.x, point.y);
            break;

         case PathPointType_Bezier3:
            switch (bidx++) {
               case 0:
                  x1 = point.x;
                  y1 = point.y;
                  break;
               case 1:
                  x2 = point.x;
                  y2 = point.y;
                  break;
               case 2:
                  x3 = point.x;
                  y3 = point.y;
                  break;
            }
            if (bidx == 3) {
               if (m_pModelMatrix) {
                  m_pModelMatrix->TransformPoint(x1, y1);
                  m_pModelMatrix->TransformPoint(x2, y2);
                  m_pModelMatrix->TransformPoint(x3, y3);
               }
               x1 += m_translateX;
               y1 += m_translateY;
               x2 += m_translateX;
               y2 += m_translateY;
               x3 += m_translateX;
               y3 += m_translateY;
               for(double t = 0.0; t <= 1.0; t += 0.01) {
                  double x = pow(1-t, 3)*m_cx + 3*pow(1-t, 2)*t*x1 + 3*(1-t)*pow(t, 2)*x2 + pow(t, 3)*x3;
                  double y = pow(1-t, 3)*m_cy + 3*pow(1-t, 2)*t*y1 + 3*(1-t)*pow(t, 2)*y2 + pow(t, 3)*y3;
                  pPixels[(int)round(y) * m_pSurface->w + (int)round(x)] = m_color;
               }

               bidx = 0;
            }
            break;
         default: break;
      }
      if (type & PathPointType_CloseSubpath) {
         // context.ClosePath ();
      }
   }
}

}