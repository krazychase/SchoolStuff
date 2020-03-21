# Midi To World

import mido

with mido.open_input() as inport:
    for msg in inport:
        print(msg.bytes())