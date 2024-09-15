# Pizzeria Simulation

The Pizzeria Simulation project aims to model the operation of a pizzeria with multiple kitchens, each with several cooks, and a command reception system. This project tackles issues such as load balancing, process and thread synchronization, and inter-process communication.

### Project Architecture

1. **Reception**
   - Command line execution via `./plazza [multiplier] [num_cooks_per_kitchen] [ingredient_replacement_time]`.
   - The *multiplier* adjusts the pizza cooking time.
   - The number of cooks per kitchen is specified.
   - The time in milliseconds for ingredient replacement is configured.
   - An interactive command-line interface to place orders and display kitchen status.

2. **Kitchens**
   - Created as child processes of the reception.
   - Each kitchen has a predefined number of cooks represented by threads.
   - Kitchens use a thread pool to manage tasks.
   - Communication between kitchens and reception via IPC.
   - Kitchens cannot accept more than `2 * N` pizzas, where `N` is the number of cooks.
   - A new kitchen process is created if needed, and kitchens inactive for more than 5 seconds will close.

3. **Pizzas**
   - Available pizza types are: Margarita, Regina, Americana, and Fantasia.
   - Each pizza has specific ingredients and a cooking time defined by the multiplier.
   - Orders are distributed among kitchens in a balanced manner.
   - Pizzas are represented by opaque objects with serialization and deserialization.

### Ingredient Management

Each kitchen has an ingredient stock that is replenished every `N` seconds (defined at startup). The initial stock contains 5 units of each ingredient.

### Abstractions and Encapsulation

- **Processes** and **Threads** are encapsulated for optimal management.
- Mutexes and condition variables are used for synchronization.
- IPC encapsulation with overloaded `<<` and `>>` operators for data serialization.

### Achievement and Grade

The project has been successfully completed with an A grade, reflecting the quality of implementation and the satisfaction of performance and functionality criteria.

![image](https://github.com/user-attachments/assets/cd83317c-6987-4695-97dc-b374d4257045)
