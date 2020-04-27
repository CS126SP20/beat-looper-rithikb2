// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>
#include "UI.h"

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;

  std::string filenames [4];

  reza::ui::SuperCanvasRef mUi;
  std::vector<reza::ui::TextInputRef> inputs;
  ci::audio::VoiceRef mVoice [4];
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
