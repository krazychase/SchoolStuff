# Midi To World

import mido
import serial

robot = serial.Serial()

with mido.open_input() as inport:
    for msg in inport:
        print(msg.bytes())
        robot.write(msg.bytes)