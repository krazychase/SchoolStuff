# Midi To World

import mido
import serial
import time

robot = serial.Serial('COM3')

with mido.open_input() as inport:
    for msg in inport:
        print(msg)
        value = str(msg.bytes()[0]) + '|'
        note = str(msg.bytes()[1]) + '|'
        velocity = str(msg.bytes()[2]) + '|'
        robot.write(value.encode())
        robot.write(note.encode())
        robot.write(velocity.encode())