# Temperature-Control-System



**Temperature Sensor Project in Embedded C**

1. **Project Objective**: Develop an embedded C program for a temperature control system that reads temperature values from a user input or EEPROM and displays them on an LCD. Additionally, the system should control a heater and a cooler based on the input temperature within the range of 20 to 40 degrees Celsius. Values outside this range should be flagged as "wrong."

2. **Hardware Components**:
   - Temperature sensor (e.g., LM35)
   - Microcontroller (AVR)
   - LCD display
   - Heater and cooler (relay modules)
   - EEPROM (optional, for storing user-defined setpoints)
   - Timer
   - Keypad
   - LEds
   - Sensor

3. **Initialization**:
   - Initialize the microcontroller and required peripherals (ADC, LCD, EEPROM, etc.).

4. **User Input**:
   - Provide a user interface to input the desired temperature setpoint, either through a keypad or serial communication.
   - Validate user input to ensure it's within the range of 20 to 40 degrees Celsius.

5. **EEPROM Storage** (latest value):
   - Implement the functionality to store and retrieve temperature setpoints from the EEPROM for persistent settings.

6. **Temperature Measurement**:
   - Continuously read the temperature from the temperature sensor using the ADC (Analog-to-Digital Converter) module.

7. **LCD Display**:
   - Display the current temperature reading on the LCD in real-time.
   - If the temperature is outside the 20-40°C range, display a "Wrong Temperature" message.

8. **Temperature Control**:
   - Implement a control algorithm to turn the heater on when the temperature falls below 20°C and turn it off when it reaches 20°C or higher.
   - Similarly, activate the cooler when the temperature exceeds 40°C and deactivate it when it falls to 40°C or lower.
   
9. **Feedback to User**:
   - Provide status updates on the LCD about the heating or cooling action being taken.

10. **Safety Features**:
    - Implement safety features, such as temperature limits and error handling, to prevent overheating or system malfunctions.

11. **Deployment**:
    - Deploy the temperature control system in the intended environment, such as a room, greenhouse, or industrial setting, as needed.

12. **Maintenance**:
    - Provide instructions for routine maintenance, including sensor calibration and system checks.
