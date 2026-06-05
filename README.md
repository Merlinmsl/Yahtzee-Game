# 🎲 Yahtzee Game (C Implementation)

A simple console-based version of the classic **Yahtzee** dice game, implemented in C.  
This project was developed as part of the **Final Assignment (Y1S1 CS/CSE)** by *M.S.L. Narangoda (IT24103215)*.

---

## 📖 Overview
This game allows a **human player** to play against a **computer AI**.  
Each round, players roll 5 dice and select a scoring category. The computer uses strategies to maximize its score. After all rounds, the program calculates the final scores and announces the winner.

---

## ✨ Key Features
- **Dice Re-roll Function**:  
  Players can hold certain dice and re-roll the rest up to three times per round.
- **Computer AI**:  
  The computer evaluates dice frequencies and makes optimal decisions based on scoring categories.
- **Automatic Score Calculation**:  
  Scores are calculated according to Yahtzee rules (Full House, Straights, Yahtzee, Chance, etc.).
- **User-Friendly Console Interface**:  
  Clear prompts guide the player through re-rolls and category selections.

---

## 🧠 Computer Player Strategy
- **Initial Roll**: Evaluates the best scoring category.
- **Selective Re-rolls**: Keeps dice with higher frequencies and re-rolls others to aim for stronger categories.
- **Category Priority**: Prefers lower-section categories (Yahtzee, Full House, Straights) before upper-section ones.
- **Final Decision**: Chooses the highest scoring available category and marks it as used.

---

## 🛠️ Challenges & Solutions
- **Random Dice Rolls**: Used `time.h` to seed the random number generator for unique rolls.
- **Frequency Calculation**: Sorted dice and counted occurrences to evaluate categories.
- **Efficiency**: Modularized code with functions and structures for clarity and debugging.
- **Conflict Resolution**: Prioritized lower-section categories with thresholds to avoid ambiguity.
- **Interface Design**: Simple numeric input prompts for re-rolls and category selection.

---

## 🚀 Future Improvements
- Add a **Graphical User Interface (GUI)** for better interaction.
- Enhance **Computer AI** with learning capabilities.
- Introduce **Multiplayer Mode** for multiple human players.

---

## 🖥️ How to Run Locally

### Prerequisites
- A C compiler (e.g., `gcc`).
- Terminal/command prompt access.

### Steps
1. Clone or download this repository:
   ``` bash
   git clone https://github.com/Merlinmsl/Yahtzee-Game.git
   cd Yahtzee-Game
   ```
2. Compile the program:
   ``` bash
   gcc yahtzee.c -o yahtzee
   ```
   *(Replace `yahtzee.c` with the actual filename if different.)*
3. Run the game:
   ``` bash
   ./yahtzee
   ```
4. Follow the on-screen instructions:
   - Enter category numbers (1–13).
   - Choose whether to re-roll (1 = Yes, 0 = No).
   - Select which dice to keep or re-roll.

---

## 📂 Project Structure
```
Yahtzee-Game/
│── yahtzee.c        # Main source code
│── README.md        # Project documentation
│── docs/            # Reports, PDFs, Word docs (optional)
│── assets/          # Images or supporting files (optional)
```

---

## 🏆 Conclusion
This project successfully implements the core mechanics of Yahtzee, providing both entertainment and a learning experience in C programming. It demonstrates modular coding, AI decision-making, and user interaction in a console environment.

---

👨‍💻 Built by **Minsara Loku Narangoda**
```

