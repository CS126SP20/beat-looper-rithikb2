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
  void play(int key);
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;

  std::string filenames [4];

  reza::ui::SuperCanvasRef mUi;
  reza::ui::Sliderf::Format sliderFormat = reza::ui::Sliderf::Format();
  std::vector<reza::ui::TextInputRef> inputs;
  reza::ui::SliderfRef sliderRef;
  int bpm;
  ci::audio::VoiceRef metronome;
  ci::audio::VoiceRef mVoice [4];
  bool isRecording = false;
  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
  struct event {
    int key;
    int timestamp;
    event(int k, int t) {
      key = k;
      timestamp = t;
    }
  };
  std::vector<event> events;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
