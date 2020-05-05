// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/audio/Voice.h>


#include "UI.h"

using namespace reza::ui;
using namespace ci;
using namespace ci::app;

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() {}

void MyApp::setup() {
  mUi = SuperCanvas::create("beat looper");
  mUi->addLabel("type file and track names and hit enter to map to keys 1-4", FontSize::MEDIUM);
  mUi->addSpacer();
  mUi->addSpacer();

  for (int i = 1; i < 5; i++) {
    mUi->addLabel("key " + std::to_string(i) + " filename:", FontSize::MEDIUM);
    inputs.push_back(mUi->addTextInput(" ", TextInput::Format()));
    mUi->addSpacer();
    mUi->addSpacer();
  }
  mUi->addLabel("track name:", FontSize::MEDIUM);
  textInputRef = mUi->addTextInput(" ", TextInput::Format());

  mUi->addLabel("use keys 1-4 to play", FontSize::MEDIUM);
  sliderFormat.precision(0);
  sliderRef = mUi->
      addSliderf("BPM", 60, 20.0, 260, sliderFormat);
  mUi->addLabel("press p to play your loop", FontSize::LARGE);
  mUi->autoSizeToFitSubviews();

  ci::audio::SourceFileRef musicFile =
      ci::audio::load(ci::app::loadAsset("metronome.wav"));
  metronome = ci::audio::Voice::create(musicFile);
  /*
  int rc = sqlite3_open("/Users/school/Library/Preferences/CLion2019.3/consoles/db/8eadde42-230e-451c-83ff-8a982a8afb35", &db_);
  if (rc == 0) {
    std::cout << "unable to connect to the database\n";
  } else {
    std::cout << "opened database successfully\n";
  }
   */
}

void MyApp::update() {

}

void MyApp::draw() {}

void MyApp::play(int key) {
  if (mVoice[key - 1]->isPlaying()) {
    mVoice[key - 1]->stop();
  }
  if (isRecording) {
    if ((std::chrono::system_clock::now() - start).count() < (60000000 * 8 / bpm)) {
      events.push_back(
          event(key, (std::chrono::system_clock::now() - start).count()));
    } else {
      isRecording = false;
      saveEvents();
    }
  }
  mVoice[key - 1]->start();
}

void MyApp::loadEvents() {
  std::ifstream readFile = std::ifstream(tracksFolder + (*textInputRef).getValue() + ".txt");
  std::string token1;
  int token2;
  readFile >> token1;
  readFile >> token2;
  while (!readFile.end) {
    readFile >> token1;
    readFile >> token2;
    fEvents.push_back(fEvent(token1, token2));
  }
}

void MyApp::saveEvents() {
  fEvents.clear();
  std::fstream checkFile;
  checkFile.open(tracksFolder + (*textInputRef).getValue() + ".txt");
  if (!checkFile.fail()) {
    loadEvents();
  }
  for (event e : events) {
    fEvents.push_back(fEvent(filenames[e.key - 1], e.timestamp));
  }
  std::ofstream trackFile = std::ofstream(tracksFolder + (*textInputRef).getValue() + ".txt");
  trackFile << "BPM: " << bpm << "\n";

  std::sort(fEvents.begin(), fEvents.end());

  for (fEvent e : fEvents) {
    trackFile << e.filename << " " << std::to_string(e.timestamp) << "\n";
  }
  trackFile.close();
}


/*

int MyApp::callback(void *NotUsed, int argc, char **argv, char **azColName) {
  return 0;
}


void MyApp::insertEvents() {
  const char *sql = "INSERT INTO TRACK (name, bpm) VALUES ('test', 70)";
                    //"VALUES ('" + trackName + "', " + std::to_string(bpm) + ");";
  char *errMsg = 0;
  int rc = sqlite3_exec(db_, sql, NULL , 0, &errMsg);
  if (rc != SQLITE_OK) {
    std::string sqlErr = "SQL error: ";
    std::cout <<  sqlErr + errMsg + "\n";
  } else {
    std::cout << "inserted into table: track\n";
  }
}
*/

void MyApp::keyDown(KeyEvent event) {
  int key = 0;
  if (event.getCode() == 13) {
    for (int i = 0; i < 4; i++) {
      filenames[i] = (*inputs[i]).getValue();
      if (filenames[i].front() == ' ') {
        filenames[i] = filenames[i].substr(1, filenames[i].size());
      }
      //std::cout << filenames[i];
      ci::audio::SourceFileRef musicFile =
          ci::audio::load(ci::app::loadAsset(filenames[i]));
      mVoice[i] = ci::audio::Voice::create(musicFile);
    }
  }
  switch (event.getChar()) {
    case 'r': {
      bpm = (*sliderRef).getValue();
      for (int i = 0; i < 4; i++) {
        metronome->start();
        std::this_thread::sleep_for(std::chrono::milliseconds((60000 / bpm)));
        metronome->stop();
      }
      start = std::chrono::system_clock::now();
      isRecording = true;
      break;
    }
    case '1': {
      key = 1;
      play(1);
      break;
    }
    case '2': {
      key = 2;
      play(2);
      break;
    }
    case '3': {
      key = 3;
      play(3);
      break;
    }
    case '4': {
      key = 4;
      play(key);
      break;
    }
    case '5': {
    }
    case '6': {
    }
    case '7': {
    }
    case '8': {
    }
  }
}

void MyApp::mouseDown(MouseEvent event) {

}

}// namespace myapp
