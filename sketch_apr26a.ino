#include <SD.h>
#include <ArduinoSound.h>

SDWaveFile waveFile;
String currentSong = "";
bool isPaused = false;

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

  AudioOutI2S.volume(5); // default volume
}

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
    else if (incomingCommand.startsWith("VOLUME UP")) {
      String volumeStr = incomingCommand.substring(7);
      int volumeLevel = volumeStr.toInt();
      if (volumeLevel >= 0 && volumeLevel <= 20) {
        AudioOutI2S.volume(volumeLevel);
        Serial.print("Volume set to: ");
        Serial.println(volumeLevel);
      } else {
        Serial.println("Invalid volume level!");
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
          currentSong = filename;
          isPaused = false;
          Serial.println("Playing: " + filename);
        } else {
          Serial.println("Cannot play the wave file!");
        }
      } else {
        Serial.println("File not found on SD: " + filename);
      }
    }
  }

  // Check if song ended naturally
  if (!AudioOutI2S.isPlaying() && !isPaused && currentSong != "") {
    Serial.println("Finished playing: " + currentSong);
    currentSong = "";
    waveFile = SDWaveFile(); // Clear waveFile
  }
}

