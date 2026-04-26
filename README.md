# CO3010 STM32 Embedded Systems Labs

## Project Summary
This repository documents a full embedded systems progression on STM32F103, from basic GPIO/timer control to a modular real-time traffic-light controller with UART-based command/telemetry exchange. The project solves a practical control problem under tight microcontroller constraints: maintaining deterministic behavior while handling concurrent timing, input events, display refresh, and host communication.

Why it matters:
- Demonstrates end-to-end embedded engineering beyond tutorial-level examples.
- Shows growth from bare interrupt loops to reusable software architecture.
- Applies real firmware design trade-offs: timing determinism, state isolation, and communication reliability.

## Scope and Progression
The codebase is organized as a lab sequence, where each stage introduces a higher level of abstraction and system complexity.

- Lab 1: GPIO fundamentals, LED patterns, button handling, and first hardware bring-up in Proteus + STM32.
- Lab 2: timer-driven logic, software timing patterns, multiplexed 7-segment control, and clock/countdown style behavior.
- Lab 3: full traffic-light finite state machine (FSM) with runtime parameter configuration via debounced multi-button input.
- Lab 4: migration from monolithic loop/FSM timing to a cooperative scheduler with periodic tasks.
- Lab 5: UART command parser + communication FSM with ADC telemetry and ACK/timeout resend logic.

Representative advanced modules:
- `CO3010_STM32_Lab_3/Lab3_FSM/Core/Src/traffic_light.c`
- `CO3010_STM32_Lab_4/Lab4_Scheduler/Core/Src/scheduler.c`
- `CO3010_STM32_Lab_5/Lab5_UART/Core/Src/uart.c`

## Key Features
- Deterministic software timing:
  - Custom timer arrays driven by periodic TIM2 interrupts.
  - 1 ms and 10 ms tick variants across labs, depending on task granularity.
- Non-trivial traffic control FSM:
  - Auto-cycle states for two-direction traffic phases.
  - Configuration states for red/yellow/green durations with guard constraints (e.g., red >= yellow).
- Robust button processing:
  - Multi-sample debouncing and long-press detection (500 ms threshold) on three input channels.
- Multiplexed 4-digit 7-segment rendering:
  - Periodic digit scan with buffered values and independent traffic countdown updates.
- Cooperative scheduler (Lab 4):
  - Delta-time task queue with static memory (no dynamic allocation).
  - Supports one-shot and periodic tasks; configured capacity up to 50 tasks.
- UART protocol with reliability behavior (Lab 5):
  - Frame-style command parsing (`! ... #`).
  - Command FSM + communication FSM.
  - Timeout-based resend (3 s) until ACK (`OK`) is received.

## System Architecture
### High-Level View
The firmware follows a layered embedded pattern:
- Hardware Abstraction Layer: STM32 HAL drivers (GPIO, TIM, UART, ADC).
- Time Base Layer: TIM2 ISR drives software timers or scheduler ticks.
- Control Layer: FSM and task scheduling logic.
- I/O Services: button input, LED/7-seg output, UART parser/transport.
- Application Layer: traffic-light behavior and host communication workflow.

### Core Components
- Timing Engine
  - `software_timer.c`: generic software timer counters and flags.
  - `scheduler.c` (Lab 4): cooperative delta-list scheduler.
- Control Logic
  - `traffic_light.c`: traffic states + transition rules + configuration modes.
  - `task.c`: periodic task wrappers (button scan, status LED, countdown updates).
- Interface Layer
  - `button.c`: debouncing/press events.
  - `led_7_segment.c`: multiplexing and number rendering.
  - `uart.c`: receive callback integration, command parser FSM, communication FSM.

### Data Flow (Representative)
1. TIM2 periodic interrupt fires.
2. Interrupt callback updates software timers or scheduler tick.
3. Main loop dispatches due work:
   - Poll/debounce buttons.
   - Advance traffic FSM.
   - Refresh 7-segment output.
   - Handle UART parsing and protocol state transitions.
4. Output drivers update GPIO/UART/ADC interactions.

## Tech Stack (and Why)
- MCU and Vendor SDK
  - STM32F103 + STM32 HAL (CubeMX-generated project scaffolding).
  - Chosen for predictable low-level control and broad industry familiarity.
- Language
  - C for deterministic execution, low overhead, and direct hardware access.
- Tooling
  - STM32CubeIDE / CubeMX `.ioc` workflow for peripheral configuration and code generation.
  - Proteus `.pdsprj` simulations for rapid hardware-logic validation without immediate physical board dependency.
- Design Patterns
  - Finite State Machines for explicit, testable control transitions.
  - Cooperative scheduling for modular periodic task composition under constrained resources.

## Setup and Usage
### Prerequisites
- STM32CubeIDE (or equivalent STM32 toolchain with CubeMX integration).
- Proteus (optional, for simulation projects included in lab folders).
- STM32F103 target board (or compatible simulation model).

### Build and Run (Minimal Reproducible Path)
1. Clone the repository.
2. Open a target `.ioc` project in STM32CubeIDE, for example:
  - `CO3010_STM32_Lab_5/Lab5_UART/lab5.ioc`
   - Other examples:
     - `CO3010_STM32_Lab_3/Lab3_FSM/Lab3_FSM.ioc`
     - `CO3010_STM32_Lab_4/Lab4_Scheduler/Lab4_Scheduler.ioc`
3. Generate code (if prompted), then build the project.
4. Flash to hardware or run the provided Proteus simulation (`.pdsprj`) in the matching lab folder.
5. For Lab 5 UART validation:
   - Send framed command: `!RST#`
   - Expect response format: `!ADC=<value>#`
   - Return `!OK#` to acknowledge and stop retransmission cycle.

## Challenges and Solutions
- Challenge: balancing multiple periodic activities (display scan, countdown, buttons, state transitions) without RTOS.
  - Solution: introduced software timers first, then refactored to a cooperative scheduler with periodic task registration.
- Challenge: user input instability (mechanical bounce) causing false transitions.
  - Solution: implemented sampled debouncing with state history buffers and explicit press/long-press event flags.
- Challenge: preserving traffic timing consistency while allowing runtime parameter changes.
  - Solution: split AUTO and CONFIG states, used temporary config variables, and enforced timing constraints before commit.
- Challenge: unreliable serial exchange due to asynchronous host behavior.
  - Solution: separated parser FSM and comm FSM, added ACK timeout and resend loop.

## Unique Engineering Contributions
- Built custom control abstractions incrementally instead of depending on a full RTOS.
- Designed modular firmware boundaries (`timer`, `scheduler`, `fsm`, `io services`) that are reusable across labs.
- Implemented a protocol-driven UART workflow with explicit fault-recovery behavior (timeout + retry).
- Demonstrated progression from direct interrupt logic to architecture-level task orchestration.

## Future Improvements
- Replace ad-hoc shared globals with structured context/state objects per module.
- Add unit-testable pure logic layers (FSM transition tables and parser logic).
- Introduce ring-buffered UART RX/TX with checksum/CRC framing.
- Add formal timing instrumentation (worst-case loop latency, task jitter metrics).
- Package scheduler and service modules as reusable embedded libraries with documented APIs.

## Repository Map
- `CO3010_STM32_Lab_1/`: foundational GPIO and simple embedded control exercises.
- `CO3010_STM32_Lab_2/`: timer-based control and 7-segment/multi-task timing exercises.
- `CO3010_STM32_Lab_3/Lab3_FSM/`: configurable traffic-light FSM implementation.
- `CO3010_STM32_Lab_4/Lab4_Scheduler/`: cooperative scheduler-based traffic-light system.
- `CO3010_STM32_Lab_5/Lab5_UART/`: UART + ADC communication FSM implementation.
- `Reports/`: lab reports and supporting documentation.

---
This project demonstrates practical embedded systems engineering: turning low-level peripherals into a structured, reliable control system with clear real-time behavior and incremental architecture maturity.