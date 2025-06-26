from typing import Dict, List, Iterable
from pathlib import Path
import os
import re
import argparse
import xml.etree.ElementTree as ET
import pprint

def parse_xml(file_path):
    """
    Parses an XML file and returns its content.
    
    :param file_path: Path to the XML file.
    :return: Parsed XML content.
    """
    try:
        with open(file_path, 'r', encoding='utf-8') as file:
            content = ET.parse(file).getroot()
        return content
    except ET.ParseError as e:
        print(f"Error parsing XML file {file_path}: {e}")
        raise
    except FileNotFoundError:
        print(f"File not found: {file_path}")
        raise


class ResourceCategory:
    def __init__(self, rc = None ):
        self.rc = None
        self.name = ""
        if rc:
            self.rc = rc
            self.name = rc.get('id')            
        
        self.resources: Dict[str, List[Dict[str, str]]] = {"Image": [], "Sound": [], "Font": []}

    def __str__(self):
        return pprint.pformat(self.resources, indent=4)
    
    def __repr__(self):
        sss = self.resources
        sss["ResourceCategory"] = self.name
        return pprint.pformat(sss, indent=4)
    
    def get_json(self):
        return {"name": self.name, "Images": self.resources["Image"],
                "Sound": self.resources["Sound"], "Font": self.resources["Font"]}

    def parse(self):
        defaults = {"path": "", "idprefix": ""}

        for el in self.rc:
            curr_res = {}
            if el.tag == "SetDefaults":
                defaults["path"] = el.get("path")
                defaults["idprefix"] = el.get("idprefix")
            
            if el.tag in ["Image", "Sound", "Font"]:
                curr_res["id"] = defaults["idprefix"] + el.get("id")
                curr_res["path"] = defaults["path"] + "/" + el.get("path")

                self.resources[el.tag].append(curr_res)

def is_filetype_match_res_cat(file_path: Path, res_cat: str) -> bool:
    filetypes = {
        "Image": ['.png', '.jpg', '.jpeg', '.gif'],
        "Sound": ['.wav', '.mp3', '.ogg', '.au'],
        "Font": ['.ttf', '.otf', '.woff', '.woff2', '.txt']
    }
    return file_path.suffix.lower() in filetypes[res_cat]

def rematch_resources_paths(rc: ResourceCategory, root: Path):
    if not root.exists():
        raise FileNotFoundError(f"Root path {root} does not exist.")
    
    for _root, dirs, files in os.walk(root):
        for filename in files:
            for rc_cat, rc_res_list in rc.resources.items():
                for i, res in enumerate(rc_res_list):
                    a = Path(filename)
                    b = Path(res['path'])
                    if a.stem.lower() == b.stem.lower() and is_filetype_match_res_cat(a, rc_cat):
                        print(f"{b} : {a}")
                        rc.resources[rc_cat][i]['old_path'] = rc.resources[rc_cat][i]['path']
                        rc.resources[rc_cat][i]['path'] = str(Path(_root) / filename)
                        break


def parse_data(content) -> List[ResourceCategory]:
    all_resources = []

    if content is None:
        raise ValueError("No content found in the XML file.")

    for resource_category in content.findall('Resources'):
        res_cat = ResourceCategory(resource_category)
        res_cat.parse()
        all_resources.append(res_cat)

    return all_resources

def gather_unmatched(ds: List[ResourceCategory]) -> List[Dict[str, str]]:
    unmatched = []
    for rc in ds:
        for rc_cat, rc_res_list in rc.resources.items():
            for res in rc_res_list:
                if rc_cat in ['Image', 'Sound', 'Font'] and 'old_path' not in res:
                    unmatched.append({
                        'ResourceCategory': rc.name,
                        'ResourceType': rc_cat,
                        'ResourceID': res['id'],
                        'ResourcePath': res['path']
                    })

    return unmatched

def export_data(ds: Iterable, output_file: str):
    """
    Exports the parsed data to a text file.
    
    :param ds: List of ResourceCategory objects.
    :param output_file: Path to the output file.
    """
    with open(output_file, 'w', encoding='utf-8') as f:
        f.write(pprint.pformat(ds, indent=4))

def argument_parser():
    parser = argparse.ArgumentParser(description="Parse an XML file and print its content.")
    parser.add_argument('-f', '--file-path', type=str, help='Path to the XML file to parse')
    parser.add_argument('-r', '--root', type=str, help='Resource directory to search for resource files')
    parser.add_argument('-o', '--output', type=str, help='Output file to save the parsed data')
    return parser.parse_args()

def argument_validator(args):
    if not args.file_path:
        raise ValueError("File path is required. Use -f or --file-path to specify the XML file.")
    if not args.root:
        raise ValueError("Root directory is required. Use -r or --root to specify the resource directory.")
    if not args.output:
        print("Output file is not specified. defaulting to 'parsed_resources.txt'.")
        args.output = 'parsed_resources.txt'
    return args

def main():
    args = argument_parser()
    args = argument_validator(args)
    content = parse_xml(args.file_path)
    ds = parse_data(content)
    
    for rc in ds:
        rematch_resources_paths(rc, Path(args.root))
    export_data(ds, args.output)

    unmatched = gather_unmatched(ds)
    # export_data(unmatched, 'unmatched_resources.txt')

if __name__ == "__main__":
    main()