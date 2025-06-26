from typing import List
from pathlib import Path
import re
import shutil

plant_list = [
    "PEASHOOTER",
    "SUNFLOWER",
    "CALTROP",
    "CORNPULT",
    "CHERRY_BOMB",
    "WALL_NUT",
    "POTATO_MINE",
    "SNOW_PEA",
    "CHOMPER",
    "REPEATER",
    "PUFF_SHROOM",
    "SUN_SHROOM",
    "FUME_SHROOM",
    "GRAVE_BUSTER",
    "HYPNO_SHROOM",
    "SCAREDY_SHROOM",
    "ICE_SHROOM",
    "DOOM_SHROOM",
    "LILY_PAD",
    "SQUASH",
    "THREEPEATER",
    "TANGLE_KELP",
    "JALAPENO",
    "SPIKEWEED",
    "TORCHWOOD",
    "TALL_NUT",
    "SEA_SHROOM",
    "PLANTERN",
    "CACTUS",
    "BLOVER",
    "SPLIT_PEA",
    "STARFRUIT",
    "PUMPKIN",
    "MAGNET_SHROOM",
    "CABBAGE_PULT",
    "FLOWER_POT",
    "KERNEL_PULT",
    "COFFEE_BEAN",
    "GARLIC",
    "UMBRELLA_LEAF",
    "MARIGOLD",
    "MELON_PULT",
    "GATLING_PEA",
    "TWIN_SUNFLOWER",
    "GLOOM_SHROOM",
    "CATTAIL",
    "WINTER_MELON",
    "GOLD_MAGNET",
    "SPIKEROCK",
    "COB_CANNON",
    "IMITATER",
    "POT"
]

zombie_list: List = [
    "backup",
    "balloon",
    "bobsled",
    "boss",
    "bossdriver",
    "bungi",
    "catapult",
    "charred",
    "dancer",
    "digger",
    "disco",
    "dolphinrider",
    "duckytube",
    "football",
    "gargantuar",
    "imp",
    "jackbox",
    "Jackson",
    "ladder",
    "paper",
    "pogo",
    "polevaulter",
    "screendoor",
    "snorkle",
    "target",
    "yeti",
    "zamboni",
    "zambonidriver",
]

misc_list = [
    "accessories",
    "coin",
    "CrazyDave",
    "credits",
    "Diamond",
    "Digger",
    "eyewear",
    "facialhair",
    "fire",
    "firepea",
    "hair",
    "hammer",
    "hats",
    "lawnmower",
    "poolcleaner",
    "leaf",
    "portal",
    "puff",
    "rain",
    "rake",
    "selectorscreen",
    "slotmachine",
    "splash",
    "sprout",
    "stinky",
    "sun",
    "tidbits",
    "tree",
    "zengarden",
    "roofcleaner",
]

def validate_move_dict(item_name, move_dict: dict):
    """
    validates the move dictionary with the user, it prints all items with indexes, and asks the user to confirm the move
    the user has the option to remove a single item - by index, or to add a new item
    :param move_dict: dictionary with source and destination paths
    """
    tmp = list(move_dict.keys())
    if not tmp:
        return move_dict
    src_dir = Path(tmp[0]).parent

    tmp = list(move_dict.values())
    if not tmp:
        return move_dict
    dst_dir = Path(tmp[0]).parent

    print(f"item name: {item_name}")
    for i, (src, dst) in enumerate(move_dict.items()):
        print(f"{i}: {src.name}")

    while True:
        action = input("Enter 'r' to remove an item, 'a' to add a new item, or 'c' to confirm:\n >> ")
        action = action.lower().strip()
        if action == 'r':
            index = int(input("Enter the index of the item to remove:\n >> "))
            if 0 <= index < len(move_dict):
                del move_dict[list(move_dict.keys())[index]]
            else:
                print("Invalid index.")
        elif action == 'a':
            src = input("Enter the source path:\n >> ")
            dst = input("Enter the destination path:\n >> ")
            full_src = (src_dir / src).resolve()
            full_dst = (dst_dir / dst).resolve()
            if not full_src.exists():
                print(f"Source path {full_src} does not exist.")
                continue
            if not full_dst.exists():
                print(f"Destination path {full_dst} does not exist.")
                continue
            move_dict[full_src] = full_dst
        elif action == 'c':
            break
        else:
            print("Invalid action.")

    return move_dict

def gather(item_name: str, source_dir_: str, target_dir_: str):
    source_dir = Path(source_dir_).resolve()
    target_dir = Path(target_dir_).resolve()
    rule = re.compile(rf"{item_name}_(.*).(png|jpg)", re.IGNORECASE)

    if not target_dir.exists():
        target_dir.mkdir(parents=True, exist_ok=True)

    if not source_dir.exists():
        raise FileNotFoundError(f"Source directory {source_dir} does not exist.")

    move_dict = {}

    for file in source_dir.iterdir():
        if file.is_file() and rule.match(file.name):
            fsrc = file.resolve()
            fdst = target_dir / file.name
            move_dict[fsrc] = fdst

    move_dict = validate_move_dict(item_name, move_dict)
    for src, dst in move_dict.items():
        shutil.move(src, dst)


def sort_plants():
    plant_list.sort(key=len, reverse=True)
    for plant in plant_list:
        print(f"\nGathering resources for plant: {plant}")
        dir_name = plant.lower().replace("_", " ").capitalize().replace(" ", "")
        gather(dir_name, "resources", f"resources/plants/{dir_name}")

def sort_zombies():
    zombie_list = [f"Zombie_{zombie}".upper() for zombie in zombie_list]
    zombie_list.sort(key=len, reverse=True)
    for zombie in zombie_list:
        print(f"\nGathering resources for zombie: {zombie}")
        dir_name = zombie.lower().replace("_", " ").capitalize().replace("Zombie ", "")
        gather(zombie, "resources", f"resources/zombies/{dir_name}")

def sort_misc():
    misc_list.sort(key=len, reverse=True)
    for misc in misc_list:
        print(f"\nGathering resources for misc item: {misc}")
        dir_name = misc.lower().replace("_", " ").capitalize().replace(" ", "")
        gather(misc, "resources", f"resources/miscellaneous/{dir_name}")

def main():
    sort_plants()
    sort_zombies()
    sort_misc()


if __name__ == "__main__":
    main()
