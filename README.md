# Pretty's Coffee Shop — Coffee Shop Management System

A console-based Coffee Shop Management System written in C. The program lets customers browse a coffee menu, build an order with add-ons, and confirm it (saved to a receipt file), while admins can log in and manage stock.

---

## Overview

On startup, the program shows a welcome banner and routes the user into one of two panels:

- **Admin Panel** — password-protected login, then add new items to stock
- **Customer Panel** — browse the coffee menu, add items and add-ons, delete items from the current order, and confirm the order

Every confirmed order is written to `coffeeshop.txt` and immediately read back and displayed as a receipt.

---

## Features

- Coffee menu with 5 items (Americano, Latte, Mocha, Cappuccino, Macchiato)
- Add-ons: Milk, Honey, Sugar, Flavour
- Add / delete items from the current order before confirming
- Order total calculated automatically
- Order receipt saved to file (`coffeeshop.txt`) and read back after confirmation
- Admin login (name + password, max 2 attempts) to add new stock items
- Stock summary showing quantity and total value per item

---

## Tech Stack

| Component | Details |
|-----------|---------|
| Language  | C |
| Libraries | `stdio.h`, `string.h` |
| Storage   | Plain text file (`coffeeshop.txt`) |

---

## Getting Started

### Prerequisites
- A C compiler (GCC recommended)

### Compile

```bash
gcc coffeeshop_management.c -o coffeeshop_management
```

### Run

```bash
./coffeeshop_management
```

---

## Usage

**Main Menu**
```
1. Main Menu
2. Exit
```
Choosing option 1 leads to a choice between the Admin panel and the Customer panel.

**Customer Panel**
1. Choose any option (1–5) to open the coffee menu.
2. Enter a number (1–5) to add a coffee item, or 6 to add add-ons.
3. Enter 7 to view and delete an item already added.
4. Enter 8 to confirm the order — the total is shown and the receipt is written to `coffeeshop.txt`, then printed back to the console.

**Admin Panel**
1. Enter your name.
2. Enter the password (`12345`). You get up to 2 attempts.
3. On success, enter the number of new items to add, then the name, price, and quantity of each.
4. A summary of current stock is printed at the end.

---

## Sample Run

```
Enter your choice: 1
1. Admin panel        2. Customer panel

Choose your panel: 2
Choose One: 1

Coffee Menu:
1. Americano: $5.0
2. Latte: $3.50
...
Enter customer choice: 1
Added Americano: $5.00
Enter customer choice: 2
Added Latte: $3.50
Enter customer choice: 8

Order Cofirmed. Total Cash: $8.50
Thanks for your ordering.

Read the file.

Order Details:

Item:
1. Americano: $5.00
2. Latte: $3.50

Total: $8.50
```

---

## Project Structure

```
coffeeshop_management.c        # Main source file (menu, order, stock, file I/O logic)
coffeeshop_management.txt       # Auto-generated order receipt (created at runtime)
```

---

## Known Limitations

- **Add-on price bug:** When an add-on (Milk/Honey/Sugar/Flavour) is added, its price is accumulated with `price[count] += ...` into a slot that hasn't been initialized yet, so the *individual* line price stored for that add-on in the receipt can show an incorrect (garbage) value, even though the **order total remains correct**. This is present in the original logic and has been left untouched.
- `admin()`'s `scanf("%s", &name)` passes the address of the whole array rather than the array itself; it still works in practice but triggers a compiler warning.
- Order and stock arrays have fixed sizes (`price[50]`, `names[50][20]`, `stock[10]`) with no bounds checking.
- Only one order can be stored at a time — confirming a new order overwrites `coffeeshop.txt`.
- No persistent stock storage — stock added via the admin panel is not saved to a file, so it resets every run.

---

## Future Improvements

- Fix the add-on price initialization bug so individual line items always show the correct price
- Add input validation to prevent invalid menu choices or out-of-range array access
- Persist stock data to a file so it's retained between runs
- Support multiple simultaneous orders/customers
- Replace fixed-size arrays with dynamic memory allocation
- Add a proper receipt format with item quantities and timestamps

---

## License

This project was developed for academic/learning purposes. Free to use and modify.
