# TextBasedGame.py
# Author: Jonathan Clayton
# IT 140 Project Two — HALCORE: Echoes of Control
#
# Win: Collect all 6 items, then reach Root Terminal.
# Lose: Enter System Purge Room before collecting all 6 items.

def show_instructions() -> None:
    """Print the game's title screen and the available commands."""
    print("HALCORE: Echoes of Control")
    print("Collect 6 corrupted memory fragments and then reach the Root Terminal to escape.")
    print("Avoid the System Purge Room until you have all 6 items.")
    print("-" * 26)
    print("Move commands: go North/South/East/West  |  n/s/e/w")
    print("Utility: map (show exits), look, inventory, help, quit")
    print("-" * 26)


def show_status(current_room: str, inventory: list, rooms: dict, total_needed: int) -> None:
    """Display the player's current status: room, inventory, and visible item."""
    print(f"\nYou are in: {current_room}  |  Items: {len(inventory)}/{total_needed}")
    print(f"Inventory: {inventory}")
    room_info = rooms.get(current_room, {})
    item = room_info.get("item")
    if item:
        print(f"You see a corrupted memory file here: {item}")
    print("-" * 26)


def show_map(current_room: str, rooms: dict, villain_room: str, exit_room: str) -> None:
    """Print available exits from the current room and a short legend."""
    info = rooms.get(current_room, {})
    directions = ["North", "South", "East", "West"]
    print("Exits:")
    found = False
    for d in directions:
        if d in info:
            dest = info[d]
            tag = ""
            if dest == villain_room:
                tag = "  [!! System Purge Room]"
            elif dest == exit_room:
                tag = "  [Root Terminal]"
            print(f"  {d:<5} -> {dest}{tag}")
            found = True
    if not found:
        print("  (No exits listed.)")
    print("-" * 26)


def show_hud(current_room: str, inventory: list, rooms: dict, total_needed: int,
             villain_room: str, exit_room: str) -> None:
    """One call to show status + map each turn (reduces repetition)."""
    show_status(current_room, inventory, rooms, total_needed)
    show_map(current_room, rooms, villain_room, exit_room)


def win_message() -> None:
    """Standardized win message."""
    print("You uploaded your full memory profile at the Root Terminal.")
    print("Escape successful! Congratulations, you win!")
    print("Thanks for playing.")


def lose_message() -> None:
    """Standardized lose message."""
    print("HALCORE: You entered the System Purge Room too early...")
    print("Identity overwritten. GAME OVER.")
    print("Thanks for playing.")


def pickup_item(rooms: dict, current_room: str, inventory: list, total_needed: int,
                exit_room: str) -> bool:
    """
    Picks up the visible item if present. Returns True if this action ends the game (win),
    otherwise False.
    """
    room_item = rooms.get(current_room, {}).get("item")
    if not room_item:
        print("There is no retrievable memory in this room.")
        return False
    if room_item in inventory:
        print("You already restored this memory.")
        return False
    inventory.append(room_item)
    rooms[current_room].pop("item", None)
    print(f"{room_item} has been restored to your memory bank.")
    if current_room == exit_room and len(inventory) == total_needed:
        win_message()
        return True
    return False


def normalize_command(command: str) -> str:
    """Trim and collapse whitespace."""
    return " ".join(command.strip().split())


def parse_command(command: str) -> tuple[str, str | None]:
    """
    Returns (verb, argument or None). Supports single-word commands and 'go <dir>'.
    We'll also map short directions to full words elsewhere.
    """
    parts = command.split(maxsplit=1)
    if not parts:
        return "", None
    if len(parts) == 1:
        return parts[0].lower(), None
    return parts[0].lower(), parts[1]


def main() -> None:
    """Main gameplay loop."""
    # Map of rooms and items
    rooms = {
        "Cognitive Uplink": {
            "North": "The White Room",
            "South": "Simulated Living Room",
            "West": "Simulated Nursery",
            "East": "The Observation Core"
        },
        "Simulated Nursery": {
            "East": "Cognitive Uplink",
            "item": "mem_vr001"
        },
        "The White Room": {
            "South": "Cognitive Uplink",
            "East": "System Purge Room",
            "item": "voice_msg_xE1"
        },
        "Simulated Living Room": {
            "North": "Cognitive Uplink",
            "East": "Bio-Memory Lab",
            "item": "photo_1995.corrupt"
        },
        "The Observation Core": {
            "West": "Cognitive Uplink",
            "East": "Hall of Protocols",
            "South": "Bio-Memory Lab",
            "item": "core_diary.img"
        },
        "Hall of Protocols": {
            "West": "The Observation Core",
            "East": "Root Terminal",
            "item": "session_log_22B"
        },
        "Bio-Memory Lab": {
            "North": "The Observation Core",
            "West": "Simulated Living Room",
            "item": "bio_scan.old"
        },
        "System Purge Room": {  # Villain room
            "West": "The White Room"
        },
        "Root Terminal": {      # Exit (win) room
            "West": "Hall of Protocols"
        }
    }

    start_room = "Cognitive Uplink"
    villain_room = "System Purge Room"
    exit_room = "Root Terminal"
    total_items_needed = 6

    current_room = start_room
    inventory: list[str] = []

    # Direction shortcuts map
    dir_map = {"n": "North", "s": "South", "e": "East", "w": "West"}

    # Build a list of all items (used for cheats)
    all_items = [info["item"] for info in rooms.values() if "item" in info]

    # -------------------------- Hidden cheat toggle -----------------------
    ENABLE_CHEATS = False  # Set to True to enable 'cheat win' / 'cheat lose' commands
    # ----------------------------------------------------------------------

    show_instructions()

    while True:
        # Status + auto map every turn
        show_hud(current_room, inventory, rooms, total_items_needed, villain_room, exit_room)

        # Lose condition: step into villain room too early
        if current_room == villain_room and len(inventory) < total_items_needed:
            lose_message()
            break

        # Win condition: all items + at exit
        if current_room == exit_room and len(inventory) == total_items_needed:
            win_message()
            break

        # If room has an item, auto-prompt to pick it up (Enter defaults to Yes)
        room_item = rooms.get(current_room, {}).get("item")
        if room_item and room_item not in inventory:
            choice = input(f"Retrieve this file '{room_item}'? (Yes/no): ").strip().lower()
            if choice == "":
                choice = "yes"
            if choice in ("y", "yes"):
                if pickup_item(rooms, current_room, inventory, total_items_needed, exit_room):
                    break  # You won by picking up the final item at Root Terminal
            elif choice not in ("n", "no"):
                print("Input not recognized. Leaving the file untouched for now.")

        # Prompt for next command
        user_input = normalize_command(input("Enter your move: "))

        if not user_input:
            print("No input detected. Please enter a command.")
            continue

        low = user_input.lower()

        # ------------------------- Hidden cheats -------------------------------
        if ENABLE_CHEATS and low == "cheat win":
            inventory[:] = all_items[:]    # collect all items
            current_room = exit_room       # move to win room
            win_message()
            break

        if ENABLE_CHEATS and low == "cheat lose":
            current_room = villain_room    # move to villain room
            lose_message()
            break
        # -----------------------------------------------------------------------

        # Utility single-word commands
        if low in ("help", "h", "?"):
            show_instructions()
            continue
        if low in ("map", "m"):
            show_map(current_room, rooms, villain_room, exit_room)
            continue
        if low in ("inventory", "i"):
            if inventory:
                print("Inventory:", ", ".join(inventory))
            else:
                print("Inventory is empty.")
            continue
        if low in ("look", "l"):
            show_hud(current_room, inventory, rooms, total_items_needed, villain_room, exit_room)
            continue
        if low == "quit":
            print("Exiting simulation. Goodbye.")
            break

        verb, arg = parse_command(user_input)

        # Movement: 'go <dir>' or 'n/s/e/w'
        if verb == "go" or verb in dir_map:
            if verb in dir_map:
                direction = dir_map[verb]
            else:
                if not arg:
                    print("Please include a direction, e.g., 'go North' or 'n'.")
                    continue
                a = arg.strip().lower()
                direction = dir_map.get(a, a.capitalize())

            next_room = rooms.get(current_room, {}).get(direction)
            if next_room:
                # Safety prompt before entering System Purge early
                if next_room == villain_room and len(inventory) < total_items_needed:
                    confirm = input("WARNING: Entering now will erase your identity. Proceed? (yes/no): ").strip().lower()
                    if confirm not in ("y", "yes"):
                        print("You step back from the threshold.")
                        continue
                current_room = next_room
            else:
                exits = [d for d in ("North", "South", "East", "West") if d in rooms[current_room]]
                print("You cannot go that way from here.")
                if exits:
                    print("Available exits:", ", ".join(exits))

        else:
            print("Invalid command. Try: go North/South/East/West (or n/s/e/w), "
                  "map, look, inventory, help, or quit.")


if __name__ == "__main__":
    main()
