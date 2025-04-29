/**
* @file sketch_apr26a.ino
*
* @brief Sending commands to the soundboard, to play/pause 
* and adjust volume
*
* @note This project was created with assistance from ChatGPT and the following reference:
* -Link:https://docs.arduino.cc/tutorials/generic/wave-playback/#troubleshoot
*
* @author Evelyn Dominguez & Chat GPT
*/

#include <SD.h>
#include <ArduinoSound.h>

SDWaveFile waveFile;
String currentSong = "";
bool isPaused = false;
int currentVol = 5; 

void setup() {
  Serial.begin(115200);
  Serial1.begin(115200);

  while (!Serial) {
    ; // Wait for Serial Monitor
  }

  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("SD initialization failed!");

    while (1);
  }
  Serial.println("SD card initialized.");
  AudioOutI2S.volume(currentVol); // default volume
}

//equalIgnorecase: ignores differences in uppercase and lowercase letters
void loop() {

  
if (Serial1.available()) {
    String incomingCommand = Serial1.readStringUntil('\n');
    incomingCommand.trim(); // Remove \r, \n, spaces at start and end

    Serial.print("Received command: ");
    Serial.println(incomingCommand);

    if (incomingCommand.equalsIgnoreCase("PAUSE")) {
      if (AudioOutI2S.isPlaying()) {
        AudioOutI2S.pause();
        isPaused = true;
        Serial.println("Playback paused.");
      }
    }
    else if (incomingCommand.equalsIgnoreCase("PLAY")) {
      //if no audio and a song is loaded resume playback
      if(!AudioOutI2S.isPlaying() && !currentSong.isEmpty()) {
        AudioOutI2S.play(waveFile);
        isPaused = false;
        Serial.println("Playback resumed.");
      }
    }
    //control volume: AudioOutI2S.volume(level) 
    //level is between 0 and 20
    else if (incomingCommand.equalsIgnoreCase("VOLUME UP")) {
      if (currentVol < 20){
      currentVol ++;
      AudioOutI2S.volume(currentVol);
      Serial.print("Volume increase to: ");
      Serial.println(currentVol);
      }
    }
   else if (incomingCommand.equalsIgnoreCase("VOLUME DOWN")) {
      //lowers volume
      if (currentVol >= 0) {
        currentVol --;
        AudioOutI2S.volume(currentVol);
        Serial.print("Volume decrease to: ");
        Serial.println(currentVol);
      }
    }

    else {
      // Assume new song name
      String filename = incomingCommand + ".wav";
      if (SD.exists(filename.c_str())) {
        if (AudioOutI2S.isPlaying()) {
          AudioOutI2S.stop();
          delay(100); // Allow I2S hardware to reset
        }

        waveFile = SDWaveFile(filename.c_str());

        if (waveFile && AudioOutI2S.canPlay(waveFile)) {
          AudioOutI2S.play(waveFile);
          delay(100);
          while (!AudioOutI2S.isPlaying()){
            delay(10);
          }
          currentSong = filename;
          isPaused = false;
          Serial.println("Playing: " + filename);
        } 
        else {
          Serial.println("Cannot play the wave file!");
        }
      } 
      else {
        Serial.println("File not found on SD: " + filename);
      }
    }
  }

  // Check if song ended naturally
  if (!AudioOutI2S.isPlaying() && !isPaused && currentSong != "") {
    Serial.println("Finished playing: " + currentSong);
    currentSong = "";
    //waveFile = SDWaveFile(); // Clear waveFile
  }
}

