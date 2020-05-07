# Beat Looper

Author: Rithik Booreddy

---
#### Project Summary
Beat Looper will provide an interface for looping local audio clips to create simple instrumentals. There will be an 4 
button layout that can be interacted with using the keyboard (numbers 1 to 4). The application will also be able to
save projects to a file system.

#### Background Knowledge
I enjoy creating instrumentals so I would like to see a Cinder Application that can help accomplish this task. Creating 
complex rhythms using percussive sounds is difficult on normal DAWs so a keyboard-based app that functions similarly to
an AKAI MP would make this aspect of music production easier. 

#### External Libraries
The application will use the Cinder-UI Cinder Block to create the UI interface. (https://github.com/rezaali/Cinder-UI)

#### Timeline
* Week 1:
    * Create button layout and map keys to buttons.
    * Incorporate sound clip loading with buttons by allowing user to type filepath.
* Week 2:
    * Implement looping system and audio playback.
* Week 3:
    * Implement ability to save current project with a file system.

#### Strech Goals
If I were to finish the Weekly Goals early, I would implement a file-to-button drag and drop feature. Additionally, 
I would allow users to export projects to their local storage as .mp3 or .wav.

#### Usage
In order to use Beat Looper, drag your .wav or .mp3 files into the assets folder. Type the name of your files and the 
track name into the text fields. Then, select a BPM, a loop count, and press F1 in order to record your two measures. 
Press F2 to stop recording, and your loop can be played back by pressing F3.

