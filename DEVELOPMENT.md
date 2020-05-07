# Development

---

- **4/20/20** Linked Cinder files
   - Modified CMake to include ciUI cinderblock

 - **4/21/20** Created Basic UI 
   - Loaded a required font for ciUI

 - **4/22/20** Audio
   - loaded .wav file of basic clap sound
   - mapped the audio to a keyboard press
   
 - **4/26/20** TextInput
   - implemented text input for filenames in asset folder
   - mapped 4 sounds using filenames from text fields
   
 - **4/30/20** BPM + Timestamping
   - implemented slider for selecting a BPM
   - saved key presses in vector for 2 4/4 measures
   
 - **5/04/20** File System
    - implemented ofstream that saves tracks in files in line by line system
    - Line: filename timestamp Ex: clap.wav 120050
    
 - **5/05/20** Persist Files + Looping
    - implemented method so that a file persists if the program is stopped
    - implemented slider for selecting a loop count
    - wrote method that plays back a sequence and loops based on loop count
    
 - **5/06/20** Fixed Bugs
    - Fixed issue where tracks of different names where overlapping in file content
    - Fixed issue where recording would not be able to stop and events would not be saved
 