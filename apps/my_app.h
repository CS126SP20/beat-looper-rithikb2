// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>
#include <sqlite3.h>
#include <cstdio>
#include <algorithm>
#include "UI.h"

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void readInputs();
  void play(int key);
  void keyDown(cinder::app::KeyEvent) override;
  void mouseDown(cinder::app::MouseEvent) override;
  static int callback(void *NotUsed, int argc, char **argv, char **azColName);
  void playLoop();
  std::string filenames [4];
  std::string trackname;
  reza::ui::SuperCanvasRef mUi;
  reza::ui::Sliderf::Format sliderFormat = reza::ui::Sliderf::Format();
  std::vector<reza::ui::TextInputRef> inputs;
  reza::ui::TextInputRef trackInputRef;
  reza::ui::SliderfRef loopSlideRef;
  reza::ui::SliderfRef bpmSlideRef;
  int bpm;
  int loopTotal = 5;
  ci::audio::VoiceRef metronome;
  ci::audio::VoiceRef mVoice [4];
  ci::audio::VoiceRef sound;
  int loopCount = 0;
  struct loopVoice {
    std::string filename;
    ci::audio::VoiceRef sound;
    loopVoice(std::string f, ci::audio::VoiceRef s){
      filename = f;
      sound = s;
    }
  };
  std::vector<loopVoice> loopVoices;
  bool isRecording = false;
  bool isLooping = false;
  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
  //std::chrono::nanoseconds wait;
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
  std::vector<event> events;
  void saveEvents();
  void loadEvents();
  std::string tracksFolder = "/Users/school/Cinder/my-projects/final-project-rithikb2/assets/tracks/";
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
