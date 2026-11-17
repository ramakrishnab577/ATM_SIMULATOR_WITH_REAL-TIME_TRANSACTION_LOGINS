
[README .md](https://github.com/user-attachments/files/34982504/README.md)
<div align="center">

# 🏧 Embedded ATM Simulator Using ARM7 LPC21xx

### A Modular C-Based ATM Simulation with LCD, Matrix Keypad, RTC and UART

![Language](https://img.shields.io/badge/Language-Embedded%20C-blue?style=for-the-badge)
![Controller](https://img.shields.io/badge/Controller-ARM7%20LPC21xx-orange?style=for-the-badge)
![Interface](https://img.shields.io/badge/Interface-LCD%20%7C%20Keypad%20%7C%20UART-green?style=for-the-badge)
![Type](https://img.shields.io/badge/Type-Embedded%20Systems-purple?style=for-the-badge)

</div>

---

## 📌 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Technical Concepts Used](#-technical-concepts-used)
- [System Architecture](#-system-architecture)
- [System Workflow](#-system-workflow)
- [Hardware Interfaces](#-hardware-interfaces)
- [Authentication and PIN Management](#-authentication-and-pin-management)
- [Banking Operations](#-banking-operations)
- [Transaction History and UART Logging](#-transaction-history-and-uart-logging)
- [RTC and Interrupt System](#-rtc-and-interrupt-system)
- [Project Structure](#-project-structure)
- [Build and Execution](#-build-and-execution)
- [Usage Instructions](#-usage-instructions)
- [Screenshots](#-screenshots)
- [Project Highlights](#-project-highlights)
- [Learning Outcomes](#-learning-outcomes)
- [Current Limitations](#-current-limitations)
- [Future Improvements](#-future-improvements)
- [Skills Demonstrated](#-skills-demonstrated)
- [Contributing](#-contributing)

---

## 📊 Project Statistics

| Property | Details |
|---|---|
| Programming language | Embedded C |
| Target | ARM7 LPC21xx family (`<lpc21xx.h>`) |
| Source organization | Multiple `.c` and `.h` modules |
| User input | 4 × 4 matrix keypad |
| Display | Character LCD in 8-bit mode |
| Communication | UART0, configured for 9600 baud |
| Timekeeping | On-chip RTC |
| Event handling | External interrupt EINT1 |
| Transaction history | Up to 10 entries in RAM |

## 🔍 Overview

This project implements an **embedded ATM simulator** in C for an ARM7-based LPC21xx microcontroller. Users interact with a character LCD and a 4 × 4 keypad to authenticate, check their balance, withdraw or deposit money, change their PIN, inspect recent transactions and log out.

The application integrates **GPIO, LCD control, keypad scanning, UART serial output, the real-time clock (RTC), and an external interrupt**. Transaction details and status messages are transmitted through UART0. The provided implementation is a learning-oriented simulation: balances and transaction history are held in RAM, not in a bank database.

## ✨ Features

### 🔐 Authentication
- Account number verification against a configured account number.
- PIN-based login with masked keypad entry on the LCD.
- Incorrect PIN attempt counter and warning after three failed attempts.
- PIN change after checking the existing PIN.

### 💰 Banking Functions
- **Balance enquiry** — displays the current balance on the LCD and sends details to UART.
- **Withdrawal** — subtracts a requested amount when sufficient balance is available.
- **Deposit** — adds the entered amount to the current balance.
- **Transaction history** — displays recent deposit/withdrawal records through UART.
- **Logout** — ends the active menu session and returns to login.

### 🖥️ Embedded Interfaces
- 4 × 4 matrix keypad for menu selection and numeric input.
- Character LCD for menus, prompts, balances and status messages.
- RTC-based date and time display.
- UART0 serial output for transaction records and status information.
- EINT1-triggered date/time setting flow.
- GPIO-driven alert indication on P0.2.

## 🧠 Technical Concepts Used

| Concept | Application |
|---|---|
| Embedded C | Peripheral control and ATM application logic |
| GPIO | Keypad scanning, LCD signals and alert output |
| Bitwise operations | Register masking and peripheral configuration |
| Matrix scanning | Row/column-based keypad detection |
| LCD interfacing | 8-bit commands, character and number display |
| UART | Serial transaction logging |
| RTC | Reading and setting date/time |
| Interrupts | EINT1 event flag and RTC settings workflow |
| Structures | In-memory transaction history entries |
| Arrays | Keypad lookup table and circular-style bounded history |
| Modular programming | Separate files for device drivers and application functions |

## 🏗️ System Architecture

<img width="1592" height="872" alt="Screenshot 2026-11-17 221750" src="https://github.com/user-attachments/assets/2332086b-5c39-4750-bd66-2b28dc0db562" />


**Core modules:** `main.c` initializes peripherals; `atm_run.c` controls authentication and the menu; `transaction.c` handles balance, deposit and withdrawal; `transaction_history.c` maintains recent records; `lcd.c`, `kpm.c`, `uart.c`, `rtc.c` and `interrupt.c` implement hardware-related functionality.

## ⚙️ System Workflow

```text
Power On / Reset
       |
       v
Initialize Keypad, LCD, RTC, EINT1 and UART0
       |
       v
Display Welcome Message and RTC
       |
       v
Enter Account Number --> Invalid? Retry
       |
       v
Enter PIN -----------> Invalid? Show Warning / Retry
       |
       v
Login Successful
       |
       v
ATM Menu
  |-- 1: Balance Enquiry
  |-- 2: Withdrawal
  |-- 3: Deposit
  |-- 4: Change PIN
  |-- 5: Transaction History
  `-- 6: Exit / Logout
       |
       v
Return to Login
```

The menu is implemented with keypad input and a `switch` statement. The EINT1 event flag is checked in the application flow to invoke date/time configuration.

## 🔌 Hardware Interfaces

The following pin assignments are taken from the provided headers and drivers. Confirm the final wiring against the specific LPC21xx development board and schematic.

| Peripheral | Connection / Configuration |
|---|---|
| LCD data D0–D7 | P0.8–P0.15 |
| LCD RS | P0.16 |
| LCD RW | P0.18 |
| LCD EN | P0.17 |
| Keypad rows R0–R3 | P1.16–P1.19 |
| Keypad columns C0–C3 | P1.20–P1.23 |
| UART0 TXD0 / RXD0 | P0.0 / P0.1 via pin function selection |
| EINT1 | P0.3 (configured as external interrupt function) |
| Alert GPIO | P0.2 |

The LCD driver selects **8-bit, 2-line mode**. The keypad lookup table is:

<img width="344" height="590" alt="Screenshot 2026-11-17 222800" src="https://github.com/user-attachments/assets/d09e05de-cb9d-4cc2-863c-b8fc838d0224" />
## 🔐 Authentication and PIN Management

In `atm_run.c`, the demonstration credentials are currently defined as:

```c
#define ACC_NO 1111
u32 PIN = 3333;
#define MAX 3
```

The account number is checked first. After a matching account number, the user enters a PIN using the keypad. A successful login displays `LOGIN SUCCESS` and emits a timestamped UART log. A failed PIN displays an error; after three failed attempts, the LCD shows `TRY AFTER 24Hrs!..` and an alert output is pulsed.

**Important:** The message about waiting 24 hours is a display warning; the provided code does **not** implement a real 24-hour lockout. The PIN is a global RAM variable and a changed PIN is **not saved across a reset**.

## 💰 Banking Operations

### Balance Enquiry

`Balance()` displays the in-memory balance and sends account, date, time, transaction type and balance information to UART0.

### Cash Withdrawal

`Withdraw()` obtains an amount from the keypad. When the amount is no greater than the current balance, it subtracts the amount, displays success, adds a history entry and sends a serial transaction report. Otherwise, it displays `Insufficient Bal..` and activates the alert GPIO.

### Cash Deposit

`Deposit()` obtains an amount from the keypad, adds it to the balance, displays confirmation, adds a history entry and sends a serial transaction report.

**Note:** The current code does not implement a real cash dispenser, cash acceptor, external account database or persistent balance storage. The initial global balance is zero unless changed at runtime.

## 📝 Transaction History and UART Logging

`transaction_history.c` defines a `History` structure containing account number, transaction type, amount and RTC date/time fields. The array is limited to **10 records** (`MAX_HISTORY 10`). When full, the oldest entry is shifted out to make room for a new one.

`Display_History()` sends the records to UART0; they are not written to a file. Records are lost after a power cycle or reset.

Illustrative UART output format:
<img width="905" height="636" alt="WhatsApp Image 2026-11-16 at 6 59 26 PM" src="https://github.com/user-attachments/assets/4699f2be-8ff0-4d99-ac75-5a63fce964df" />

The UART module uses the MCU's UART0 peripheral, with baud-rate configuration defined in `uart_defines.h` (`BAUD 9600`). A serial terminal can be used to inspect login, logout, balance and transaction messages.

## 🕒 RTC and Interrupt System

`rtc.c` initializes the on-chip real-time clock, reads seconds/minutes/hours/day/month/year, displays the current date and time on the LCD and provides keypad-driven date/time setting menus.

`interrupt.c` installs an EINT1 interrupt service routine. The ISR sets a shared `flag`; the main application checks that flag and calls `Set_date_time()`. This separates the interrupt event from the interactive LCD/keypad settings interface.

## 📁 Project Structure

```text
ATM_SIMULATOR/
├── main.c                   # Peripheral initialization and entry point
├── atm_run.c                # Login, PIN change, menu and main loop
├── atm_run.h
├── transaction.c            # Balance, withdrawal and deposit
├── transaction.h
├── transaction_history.c    # Recent transaction records
├── Transaction_history.h    # History function declarations
├── lcd.c                    # Character LCD driver
├── lcd.h
├── lcd_defines.h            # LCD commands and pin assignments
├── kpm.c                    # Matrix keypad scanning and input
├── kpm.h
├── kpm_defines.h            # Keypad pin definitions
├── uart.c                   # UART0 output routines
├── uart.h
├── uart_defines.h           # UART configuration
├── rtc.c                    # RTC and date/time settings
├── rtc.h
├── interrupt.c              # EINT1 handler and setup
├── interrupt.h
├── delay.c                  # Software delays
├── delay.h
├── defines.h                # Register bit-operation macros
└── types.h                  # Integer and floating-point aliases
```

> **Case sensitivity:** The archive contains `Transaction_history.h`, while source files include `transaction_history.h`. Rename the header or standardize the includes when building on a case-sensitive filesystem.

## 🔧 Build and Execution

### Prerequisites

- An ARM7 LPC21xx-compatible embedded C toolchain and device header (`lpc21xx.h`).
- A matching LPC21xx target or suitable MCU simulator.
- LCD, keypad and serial-terminal connections matching the driver pin definitions.
- A startup/linker configuration appropriate to the selected microcontroller.

### Example workflow using Keil µVision

1. Create a project for the **specific LPC21xx device** used by your board.
2. Add all `.c` files from this repository to the project.
3. Include the folder containing the `.h` files in the compiler include paths.
4. Resolve header-name case mismatches and any compiler diagnostics.
5. Configure the target clock, startup code and linker settings for your device.
6. Build the firmware and program the device, or load it into a compatible simulator.
7. Connect a UART serial terminal configured for **9600 baud** (and matching frame settings).
8. Reset the target to start the ATM simulator.

The archive contains **source and header files only**; it does not include a Keil project, a Proteus schematic or a prebuilt firmware image. This documentation does not claim a verified build or simulation run.

## 🚀 Usage Instructions

1. Reset the MCU and observe initialization messages on UART and the welcome screen on the LCD.
2. Enter account number `1111` using the keypad.
3. Enter the initial PIN `3333`.
4. Select an ATM menu option using the numeric keypad.
5. For deposit or withdrawal, enter the requested amount and follow the LCD prompts.
6. View transaction history through the UART serial terminal using menu option `5`.
7. Choose `6` to log out and return to the login flow.
8. Trigger the configured EINT1 input to access the RTC date/time setting flow when the application checks the interrupt flag.

### ATM Menu

```text
1. BAL      Balance enquiry
2. WDL      Withdrawal
3. DEP      Deposit
4. PIN CHG  Change PIN
5. TRF      Transaction history (actual code behavior)
6. EX       Exit / Logout
```
<img width="1052" height="569" alt="WhatsApp Image 2026-11-16 at 6 59 19 PM" src="https://github.com/user-attachments/assets/f2b50546-5657-4554-bafa-007d10379c81" />


**Menu-label clarification:** The LCD shows `5.TRF`, but `case 5` calls `Display_History()`. The provided source does **not** implement funds transfer.

## 📸 Screenshots

Screenshots are not included in the uploaded source archive. Once you capture your actual hardware or simulation output, you can add files such as:

```text
assets/
├── welcome-screen.png
├── login-screen.png
├── atm-menu.png
├── balance-enquiry.png
├── deposit-success.png
├── withdrawal-success.png
└── uart-transaction-history.png
```
<img width="3673" height="1733" alt="WhatsApp Image 2026-11-16 at 6 59 29 PM" src="https://github.com/user-attachments/assets/f1c33a9d-ab45-44f8-a1e8-0ed7e115e45d" />
<img width="860" height="409" alt="WhatsApp Image 2026-11-16 at 6 59 25 PM" src="https://github.com/user-attachments/assets/e5dd828e-8d92-4798-8804-1a50cf4cade8" />
<img width="816" height="346" alt="WhatsApp Image 2026-11-16 at 6 59 24 PM" src="https://github.com/user-attachments/assets/94afb83b-b88e-4dbf-beaf-2e5bf98a5c89" />
<img width="956" height="501" alt="WhatsApp Image 2026-11-16 at 6 59 23 PM" src="https://github.com/user-attachments/assets/f8b39246-e9eb-4d16-9912-7249704d517a" />
<img width="1052" height="569" alt="WhatsApp Image 2026-11-16 at 6 59 19 PM" src="https://github.com/user-attachments/assets/9748633c-0316-4281-884a-fadda16b48bd" />

## 🏆 Project Highlights

- **Hardware-oriented design:** Demonstrates an ATM workflow on an ARM7 microcontroller rather than a desktop console.
- **Modular codebase:** Dedicated modules for keypad, LCD, UART, RTC, interrupts and banking logic.
- **Multiple peripheral integration:** Combines GPIO, serial communication, real-time clock and interrupts.
- **Masked PIN input:** Uses LCD feedback while accepting keypad-entered PIN digits.
- **Timestamped records:** Associates transactions with RTC date and time.
- **Bounded history:** Maintains up to ten recent deposit/withdrawal events in RAM.
- **Serial observability:** Reports important activity over UART0 for monitoring and debugging.

## 📚 Learning Outcomes

Developing this project helps practice register-level embedded C, keypad matrix scanning, LCD command/data handling, UART configuration, RTC registers, interrupt service routines, structured data storage, modular code organization and testing of stateful user interactions.

## ⚠️ Current Limitations

The following points reflect the supplied source code, not planned features:

- **Single configured account:** Account number `1111` is compiled into the application.
- **Volatile state:** PIN, balance and history are stored in RAM and do not survive reset.
- **No real 24-hour lockout:** The message is displayed, but no timed lockout is enforced.
- **No fund transfer:** Menu item `5.TRF` actually displays transaction history.
- **No receipt file generation:** Transaction details are transmitted via UART, not saved as files.
- **No session countdown:** The source does not implement an automatic session-expiration timer.
- **No confirmed hardware validation:** Board wiring, exact MCU variant and build settings were not included in the archive.
- **Review recommended:** The withdrawal path passes RTC output pointers in a different order than the other transaction paths; this should be corrected before relying on its timestamps.

## 🔭 Future Improvements

| Priority | Improvement | Benefit |
|---|---|---|
| High | Store balances and PINs in nonvolatile memory | Retain data after reset |
| High | Implement actual PIN lockout timing | Enforce failed-login protection |
| High | Correct menu labels and RTC parameter ordering | Improve accuracy and usability |
| High | Strengthen input and balance validation | Prevent invalid operations and overflow |
| Medium | Add multiple accounts and fund transfer | Expand ATM capabilities |
| Medium | Save transaction history in EEPROM/flash | Persistent audit records |
| Medium | Add a real session timeout | Automatically end inactive sessions |
| Medium | Add hardware/simulator schematics and screenshots | Make the project easier to reproduce |
| Low | Add a receipt printer interface | Physical transaction receipts |

## 🛠️ Skills Demonstrated

```text
Embedded C          Register-level programming and modular functions
ARM7 / LPC21xx      Peripheral configuration and MCU interfaces
GPIO                Digital I/O and bit manipulation
LCD                 Character display interfacing
Keypad              4x4 matrix scanning and user input
UART                Serial communication and formatted logging
RTC                 Timekeeping and date/time configuration
Interrupts          EINT1 ISR and event-flag handling
Data Structures     Arrays and structured transaction records
Application Logic   Authentication and ATM state transitions
```

## 🤝 Contributing

Suggestions, bug reports and improvements are welcome. If you extend the project, document your target MCU, toolchain, pin connections and testing procedure, and include clear reproduction steps for any reported issues.

---

<div align="center">

**Embedded ATM Simulator — Learning ARM7 Peripheral Interfacing Through a Practical C Project**

</div>
