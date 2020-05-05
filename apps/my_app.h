// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>
#include <sqlite3.h>
#include <cstdio>

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
  static int callback(void *NotUsed, int argc, char **argv, char **azColName);
  std::string filenames [4];

  reza::ui::SuperCanvasRef mUi;
  reza::ui::Sliderf::Format sliderFormat = reza::ui::Sliderf::Format();
  std::vector<reza::ui::TextInputRef> inputs;
  reza::ui::TextInputRef textInputRef;
  reza::ui::SliderfRef sliderRef;
  int bpm;
  std::string trackName = "test";
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
    bool operator < (const event& e) const
    {
      return (timestamp < e.timestamp);
    }
  };
  //void insertEvents();
  std::vector<event> events;
  void saveEvents();
  void loadEvents();
  std::string tracksFolder = "/Users/school/Cinder/my-projects/final-project-rithikb2/assets/tracks/";
  //sqlite3 *db_;
  struct fEvent {
    std::string filename;
    int timestamp;
    fEvent(std::string f, int t) {
      filename = f;
      timestamp = t;
    }
    bool operator < (const fEvent& e) const
    {
      return (timestamp < e.timestamp);
    }
  };
  std::vector<fEvent> fEvents;
};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
