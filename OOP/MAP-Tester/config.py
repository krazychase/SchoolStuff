''' MAP Tester 3.0 Config File '''

### Serial Settings
BAUD = 38400            # Multimeter BAUD
multiCOMA = 'COM12'     # Transducer Meter COM
multiCOMB = 'COM6'      # DUT Meter COM
arduinoBAUD = 38400     # Arduino BAUD
arduinoCOM = 'COM5'     # Arduino COM

### Test Point Settings
# OE Collection Points
OEVacuumTestPressure = [-10, -9.33, -6.67, -5, -3.33, -1.67, 0]
OEOneBarTestPressure = [14.5, 12.08, 9.67, 7.25, 4.83, 2.42, 0]
OETwoBarTestPressure = [29, 24.17, 19.33, 14.5, 9.67, 4.83, 0]
OEThreeBarTestPressure = [43.5, 36.25, 29, 21.75, 14.5, 7.25, 0]
OEFourBarTestPressure = [58, 48.33, 36.67, 29, 19.33, 9.67, 0]

# Engineering Test Points

# Production Test Points