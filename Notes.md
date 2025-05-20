# General Tasking

* Add random generation of upgrades
    * Implement upgrades page which randomly choose between possible upgrades


* Add end-of-round screen for restarting gamestate
    * This includes adding a 'reset' paradigm -- A good way for this could be potentially a 'setup' gamestate which defaults objects/state

-- TODOs --
* [ ] Add Quit functionality to `MainMenu`
* [x] Standardize buttons to be `SIZING_FIT` and padding of 8, 8, 15, 15

# Brickbreaker Clone Design Document

**Game Title:** TBD

### 1. Game Flow & States

The game will transition through several key states to provide a complete user experience.

* **Main Menu State:**
    * Displays options to start the game, access settings (if applicable), and quit.
    * **Action Items:**
        * * [ ] Implement "Quit" functionality to `MainMenu`.
        * * [ ] Standardize buttons to be `SIZING_FIT` and padding of `8, 8, 15, 15`.
* **Gameplay State:**
    * Core game loop where the player controls the paddle, breaks bricks, and manages the ball.
    * Includes score tracking, lives, and power-up/upgrade application.
* **Pause State:**
    * Accessible during Gameplay.
    * Allows the player to temporarily halt the game and potentially access options like resuming or returning to the main menu.
* **Upgrades State:**
    * Presented to the player at specific intervals (e.g., end of a round).
    * Allows the player to choose from a selection of randomly generated upgrades.
    * **Action Items:**
        * * [ ] Implement upgrades page which randomly choose between possible upgrades.
        * * [ ] Design and implement the UI for the upgrades page.
        * * [ ] Implement the random selection logic for upgrades.
* **End-of-Round/Level Complete State:**
    * Triggered when all bricks in a level are destroyed.
    * Displays progress, potentially awards, and offers the option to proceed or select upgrades.
    * **Action Items:**
        * * [ ] Add end-of-round screen for restarting gamestate.
        * * [ ] Implement a screen to signify the end of a round.
* **Game Over State:**
    * Triggered when the player runs out of lives.
    * Displays the final score and offers options like restarting or returning to the main menu.
* **Reset Paradigm:**
    * A 'setup' gamestate will be implemented to efficiently reset all game objects and states. This will be crucial for restarting the game after a 'Game Over' or when starting a new round/level.
    * **Action Items:**
        * * [ ] Define the `setup` gamestate for all relevant objects (paddle, ball, bricks, scores, lives, active upgrades).
        * * [ ] Integrate the `setup` gamestate into the restart logic from the 'End-of-Round' and 'Game Over' screens.

---

### 2. Core Gameplay Mechanics

* **Paddle Control:** Player controls the paddle horizontally.
* **Ball Physics:**
    * Deflection based on collision angles with paddle and bricks.
    * Consistent ball speed, potentially increasing with difficulty or specific upgrades.
* **Brick Types:**
    * Standard bricks (break on one hit).
    * Potentially introduce multi-hit bricks, indestructible bricks, or special effect bricks.
* **Scoring System:** Points awarded for destroying bricks. Bonus points for combos or specific actions.
* **Lives System:** Player starts with a set number of lives. Losing a life occurs when the ball goes off-screen.

---

### 3. Upgrade System

The upgrade system is a core feature for player progression and variety.

* **Upgrade Generation:**
    * Upgrades will be randomly chosen from a predefined pool of possible upgrades.
    * **Action Items:**
        * * [ ] Add random generation of upgrades.
        * * [ ] Define the data structure for individual upgrades (e.g., name, description, effect).
        * * [ ] Create a pool of at least 5-10 initial upgrade types (e.g., wider paddle, slower ball, extra life, multi-ball, stronger ball).
* **Upgrade Application:**
    * Upgrades will be applied immediately upon selection from the upgrades page.
    * Consider persistent upgrades (lasting for the rest of the game) versus temporary power-ups (time-limited). For now, assume persistent for simplicity.
* **Upgrade UI:**
    * The upgrades page will present 2-3 randomly selected upgrade options to the player.
    * Each option will have a clear name and description.
    * **Action Items:**
        * * [ ] Design the visual layout of the upgrade selection screen.
        * * [ ] Implement button logic for selecting an upgrade.

---

### 4. Technical Considerations & Action Items

* **Standardized Button Styling:**
    * * [ ] Ensure all buttons (especially in the Main Menu) are set to `SIZING_FIT` for their size.
    * * [ ] Apply a consistent padding of `8, 8, 15, 15` (left, top, right, bottom) to all buttons.
* **Game State Management:**
    * * [ ] Implement a robust state machine to manage transitions between Main Menu, Gameplay, Pause, Upgrades, End-of-Round, and Game Over states.
* **Asset Management:**
    * * [ ] Plan for loading and managing textures, sounds, and fonts.
* **Collision Detection:**
    * * [ ] Refine collision detection for ball-paddle, ball-brick, and ball-wall interactions.
* **"Reset" Paradigm Implementation:**
    * * [ ] Create a `setup` or `resetGameState` function that reinitializes all necessary game variables and object positions to their default values.
    * * [ ] This function should be called when starting a new game or restarting a level.

---

### 5. Future Enhancements (Post-MVP)

* **Multiple Levels:** Design different brick layouts and potentially introduce new brick types per level.
* **Power-Ups:** Introduce power-ups that drop from broken bricks (e.g., sticky paddle, laser, magnet).
* **Sound Effects & Music:** Implement audio for various game events.
* **Visual Effects:** Add particle effects for brick destruction, ball trails, etc.
* **High Score System:** Save and display top scores.
* **Difficulty Levels:** Allow players to choose different difficulties affecting ball speed, paddle size, etc.
