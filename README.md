# Potion Inventory Simulation AKA The Potion Creation Station!

A console-based potion inventory simulation inspired by role-playing games, implemented in C++. Players can manage and sort potions that boost character stats like Strength, Speed, and Health. The inventory is efficiently managed using a **Red-Black Tree**, a self-balancing binary search tree, allowing fast lookups, insertions, deletions, and sorted listings.

---

## Project Description

In many RPGs, players collect items such as potions that increase character stats. Managing these items efficiently—sorting them or finding the most effective ones—is an interesting real-world application of data structures. This project implements a potion inventory system where each potion has specific stat boosts and is stored in a Red-Black Tree.

The Red-Black Tree ensures that:

- Every node is either red or black.
- Tree height is balanced automatically through rotations and recoloring.
- Key operations like insertion, deletion, and search run in **O(log n)** time.

Each potion is represented as an object with:

- `name` (string)
- `Strength`, `Speed`, and `Health` (integers)
- `totalStats()` method to calculate the sum of all stat bonuses

The tree can be sorted by total stats or by an individual stat like Strength, Speed, or Health, allowing flexibility in inventory organization.

---

## Features

- Add potions by entering name and stat bonuses. Potion names cannot be empty. Stats are restricted to a reasonable range (0–100000).
- Delete potions by name.
- List all potions in sorted order.
- Search for a potion by name.
- Switch sorting mode (Total Stats, Strength, Speed, or Health).
- Clear all potions from inventory.
- Console-based user interface with robust input validation. Only numeric input allowed for stats and menu choices.

---

## Classes

### `Potion`
Stores potion data:

- `string name`
- `int strength, speed, health`
- `int totalStats()`
- `void print()`

### `RBTNode`
Tree node storing a `Potion`:

- Left and right children
- Parent pointer
- Red/Black color

### `RedBlackTree`
Manages the inventory:

- `insert(Potion p)`
- `remove(string name)`
- `search(string name)`
- `inorder(bool descending = true)`
- `clear()`
- Supports switching sort key (total stats or individual stat)

---

## Walkthrough

Here is a step-by-step walkthrough of using the potion inventory simulation:

1. **Start the program**:
   - Run `./potion_inventory` after compiling.
   - You are greeted with:
     ```
     Welcome to The Potion Creation Station!
     To get started, please select a potion sorting method:
     1. Total Stats
     2. Strength
     3. Speed
     4. Health
     Please select your choice!:
     ```
   - Choose a sorting method (1–4) for how the inventory will be ordered.

2. **Main Menu**:
    - Here is the Main Menu that is presented after making your sorting method:
    ```
    --- Menu ---
    1. Add Potion
    2. Display All Potions
    3. Search Potion by Name
    4. Delete Potion by Name
    5. Clear All Potions
    6. Change Sorting Method
    7. Quit
    Please select your choice!:
    ```

3. **Add a Potion**:
- Select `1`.
- Enter potion name and stats (Strength, Speed, Health).
- Stats are numeric only and limited to 0–100000.
- Example:
  ```
  Potion name: Elixir of Vitality
  Strength: 4
  Speed: 3
  Health: 5
  Potion added!
  ```

4. **Display Potions**:
- Select `2`.
- If you have potion(s) in your inventory, then all potions will be displayed sorted by the current sort key. Otherwise, you will see:
  ```
  You have no potions in your inventory to be displayed!
  ```
- Example output:
  ```
  === Potion List ===
  1. Potion of Giants - STR: 7, SPD: 5, HP: 6 (Total: 18)
  2. Elixir of Vitality - STR: 4, SPD: 3, HP: 5 (Total: 12)
  ```

5. **Search by Name**:
- Select `3` 
- If you have potion(s) in your inventory you will be prompted to enter the potion name. Otherwise, you will see:
  ```
  You have no potions in your inventory to be searched for!
  ```
- If you have potion(s) in your inventory, and the potion name is found, stats are displayed; otherwise, you see:
  ```
  Potion not found.
  ```

6. **Delete a Potion**:
- Select `4`
- If you have potion(s) in your inventory you will be prompted to enter the potion name. Otherwise, you will see:
  ```
  You have no potions in your inventory to be deleted!
  ```
- If you have potion(s) in your inventory, and the potion name is found then the potion is removed from the inventory and tree:
  ```
  This Potion has been sent into the depths of the archive, never to be found again!
  ```

7. **Clear Inventory**:
- Select `5` 
- If you have potion(s) in your inventory you will be prompted to enter the potion name. Otherwise, you will see:
  ```
  You have no potions in your inventory to be cleared!
  ```
- If you do have potion(s) in your inventory, then all potions in your inventory will be removed:
  ```
  All potions cleared!
  ```

8. **Change Sorting Method**:
- Select `6` to choose a new sort key (Total, Strength, Speed, or Health).
- Inventory will be rebuilt using the new sort key.

9. **Quit Program**:
- Select `7` to exit:
  ```
  Thank you for visiting the Potion Creation Station! Good luck with future adventures!
  ```

## Example Snapshot Run
```
Welcome to The Potion Creation Station!
To get started, please select a potion sorting method:
    1. Total Stats
    2. Strength
    3. Speed
    4. Health
Please select your choice!: 1
```
```
Now onto the Potion Main Menu....

--- Menu ---
1. Add Potion
2. Display All Potions
3. Search Potion by Name
4. Delete Potion by Name
5. Clear All Potions
6. Change Sorting Method
7. Quit
Please select your choice!: 1
```
```
Potion name: Elixir of Vitality
Strength: 4
Speed: 3
Health: 5
Potion added!
```
```
--- Menu ---
1. Add Potion
2. Display All Potions
3. Search Potion by Name
4. Delete Potion by Name
5. Clear All Potions
6. Change Sorting Method
7. Quit
Please select your choice!: 1
```
```
Potion name: Potion of Giants
Strength: 7
Speed: 5
Health: 6
Potion added!
```

```
--- Menu ---
1. Add Potion
2. Display All Potions
3. Search Potion by Name
4. Delete Potion by Name
5. Clear All Potions
6. Change Sorting Method
7. Quit
Please select your choice!: 2
```
```
=== Potion List ===

Potion of Giants - STR: 7, SPD: 5, HP: 6 (Total: 18)

Elixir of Vitality - STR: 4, SPD: 3, HP: 5 (Total: 12)
```
```
--- Menu ---
1. Add Potion
2. Display All Potions
3. Search Potion by Name
4. Delete Potion by Name
5. Clear All Potions
6. Change Sorting Method
7. Quit
Please select your choice!: 3
```
```
Enter potion name: Elixir of Vitality
Potion Found:
Name: Elixir of Vitality
Strength: 4
Speed: 3
Health: 5
Total Stats: 12
```
```
--- Menu ---
1. Add Potion
2. Display All Potions
3. Search Potion by Name
4. Delete Potion by Name
5. Clear All Potions
6. Change Sorting Method
7. Quit
Please select your choice!: 4
```
```
Enter potion name: Elixir of Vitality
This Potion has been sent into the depths of the archive, never to be found again!
```
```
--- Menu ---
1. Add Potion
2. Display All Potions
3. Search Potion by Name
4. Delete Potion by Name
5. Clear All Potions
6. Change Sorting Method
7. Quit
Please select your choice!: 6
```
```
Welcome to The Potion Creation Station!
To get started, please select a potion sorting method:
    1. Total Stats
    2. Strength
    3. Speed
    4. Health
Please select your choice!: 3
Sorting method changed!
```
```
--- Menu ---
1. Add Potion
2. Display All Potions
3. Search Potion by Name
4. Delete Potion by Name
5. Clear All Potions
6. Change Sorting Method
7. Quit
Please select your choice!: 2
```
```
=== Potion List ===

Speed Serum - STR: 2, SPD: 9, HP: 1 (Total: 12)

Potion of Giants - STR: 7, SPD: 5, HP: 6 (Total: 18)
```
```
--- Menu ---
1. Add Potion
2. Display All Potions
3. Search Potion by Name
4. Delete Potion by Name
5. Clear All Potions
6. Change Sorting Method
7. Quit
Please select your choice!: 7
Thank you for visiting the Potion Creation Station! Good luck with future adventures!
```

---

**This snapshot:** 
- Provides a condensed view of a typical run of the Potion Inventory Simulation
- Demonstrates the main functionality, including adding potions with stats, displaying the inventory sorted by the current sort key, searching for a potion by name, deleting a potion, changing the sorting method, and finally exiting the program 
- All console output matches the actual program messages, giving a clear picture of the user experience and how the Red-Black Tree maintains the inventory in sorted order.
---

## Running the Project

1. Clone the repository:

```
git clone https://github.com/yourusername/PotionCreationStation.git
```

2. Navigate to the project folder and compile:
```
g++ main.cpp RedBlackTree.cpp Potion.cpp -o potion_inventory
```

3. Run the Program:
```
./potion_inventory
```

