# ArduinoMidiKeyboard
Arduino sketch for conversion of an old piano keyboard to a USB MIDI device.


This is sketch does not use MIDI port as a part of the circuit. Instead, the MIDI input conversion is done using software:
[The Hairless MIDI Serial Bridge](https://projectgus.github.io/hairless-midiserial/)
[Loop MIDI](https://www.tobias-erichsen.de/software/loopmidi.html)
Made for a 54 key scan matrix (8x7). For figuring out your scan matrix you can use the tutorial [here](https://www.instructables.com/Figuring-out-a-Key-Matrix-Scan-Matrix/). 74HC595 shift register is required. 
*Connect everything using this diagram:*
![](https://content.instructables.com/ORIG/FUD/QBS8/KHOUFSIW/FUDQBS8KHOUFSIW.png?auto=webp&frame=1&width=483&fit=bounds&md=684afa5a35acf5695aa4037d13dfbf4e)

Have in mind whether you have pull up or down circuit configuration.
*You mind need to connect your resistors to positive voltage in case pull down doesn't work for you.*![](https://content.instructables.com/ORIG/FB3/ZS1C/I34E4WSX/FB3ZS1CI34E4WSX.png?auto=webp&frame=1&width=1024&fit=bounds&md=cb057da1e573b994cf3634d3711d56fa)

You will also need to change the bits in the code accordingly. Everything you might need to replace/change is commented out in the code. Don't forget to define your digital pins correctly.
After uploading the sketch run Hairless MIDI, change the baud rate to 57600 in the settings and connect to your serial port. After that run loopMIDI, add a new port and set it as MIDI In/Out port in Hairless MIDI.
