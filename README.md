# AVR-Dodge

A simple obstacle-dodging game built for AVR microcontrollers using a 16x2 alphanumeric LCD and a 4x4 matrix keypad. The player controls a character that moves left or right to avoid falling obstacles on the screen.

---

## 🎮 Features

- Display: 16x2 Alphanumeric LCD
- Controls: 4x4 Matrix Keypad (using left and right buttons)
- Gameplay: Randomized falling obstacles
- Microcontroller: ATmega32 (configurable)
- Real-time screen updates
- Designed for simulation via Proteus and CodeVisionAVR

---

## 🕹️ Controls

- Press the **Left** key (`4` or `←`) to move left
- Press the **Right** key (`6` or `→`) to move right

The character is shown as `#` and obstacles are `*`. If an obstacle collides with the player, the game stops and displays `Game Over`.

---

## 🛠️ How to Build and Simulate

### 🔧 Using CodeVisionAVR

1. Open the `.c` file (e.g., `AVR_Dodge.c`) in **CodeVisionAVR**.
2. Make sure the LCD library is enabled in:
Project → Configure → CodeWizardAVR → Alphanumeric LCD → Enable
3. Set your LCD port and pins (e.g., PORTC).
4. Compile the project. This will generate `.hex` and `.cof` files.
5. Optional: Use `Build All` to update all intermediate files.

### 🧪 Using Proteus

1. Open **Proteus** and create a new project.
2. Add the following components:
- ATmega32
- 16x2 Alphanumeric LCD
- 4x4 Matrix Keypad
3. Connect the LCD and keypad to the same ports used in your CodeVision configuration.
4. Load the compiled `.hex` file to the ATmega32.
5. Run the simulation and play the game!

> 💡 Tip: You can assign buttons in Proteus to keypad rows for easier testing.

---

## 📁 Project Structure

```bash
AVR-Dodge/
│
├── AVR_Dodge.c         # Main game logic
├── AVR_Dodge.hex       # Compiled HEX for Proteus simulation
├── README.md           # This file
├── .gitignore          # Git ignore rules
├── proteus.dsn         # (Optional) Proteus design file
└── CodeVision/
 ├── AVR_Dodge.cwp   # CodeVision project workspace
 ├── AVR_Dodge.cproj # CodeVision project file
 └── ...             # Intermediate files (.cof, .fct, etc.)
