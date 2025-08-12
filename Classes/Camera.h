//
// Created by judelhuu on 8/2/25.
//

#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include "nUtil.h"

using namespace util;

class Camera {
public:
  void Update(float dt) {
      if (m_target == nullptr) {
          return;
      }
      m_viewbox.x = m_target.x - m_windowWidth/2;
      m_viewbox.y = m_target.y - m_windowHeight/2;

      if (m_viewbox.x < 0) {
          m_viewbox.x = 0;
      }
      if (m_viewbox.y < 0) {
          m_viewbox.y = 0;
      }

      if (m_viewbox.x > (2*m_windowWidth - m_viewbox.w)) {
          m_viewbox.x = (2*m_windowWidth - m_viewbox.w);
      }

      if (m_viewbox.y > (m_windowHeight - m_viewbox.h)) {
          m_viewbox.y = (m_windowHeight - m_viewbox.h);
      }

      m_position = Vector2<float>((float)m_viewbox.x, (float)m_viewbox.y);
  }
  void SetTarget(const Vector2i target) {m_target = target;}

  SDL_Rect       GetViewBox() const {return m_viewbox; }
  Vector2f       GetPosition() const {return m_position;}
  static Camera& GetInstance() {static auto* instance = new Camera; return *instance; }

private:
    Camera();
    Camera(int windowWidth, int windowHeight){m_viewbox = {0,0,windowWidth, windowHeight}; m_windowWidth = windowWidth,m_windowHeight = windowHeight;}
    SDL_Rect m_viewbox;

    Vector2i m_target;
    Vector2f m_position;

    int m_windowWidth, m_windowHeight;
    static Camera* s_instance;
};



#endif //CAMERA_H
