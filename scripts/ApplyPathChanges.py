from typing import Dict, List, Union
from pathlib import Path
import json
import argparse

from parsed_resources import parsed_resources
from unmatched_resources import unmatched_resources

from parseResourcesXML import ResourceCategory, parse_xml, parse_data

def argument_parser():
    parser = argparse.ArgumentParser(description="Parse an XML file and print its content.")
    parser.add_argument('-i', '--input-file', type=str, help='intput file to read the xml data from', required=True)
    parser.add_argument('-o', '--output', type=str, help='Output file to save the parsed data')
    return parser.parse_args()

def argument_validator(args):
    if args.input_file:
        input_file_path = Path(args.input_file).resolve()
        if not input_file_path.exists():
            raise FileNotFoundError(f"Input file {input_file_path} does not exist.")

    if not args.output:
        args.output = Path("resources.json").resolve()
    return args
    

def parse_data_to_resource_categories(data: List[Dict[str, Union[str, List[Dict[str, str]]]]]) -> List[ResourceCategory]:
    resource_categories: List[ResourceCategory] = []

    for rc_dict in data:
        rc = ResourceCategory()
        rc.name = rc_dict["ResourceCategory"]
        rc.resources["Image"] = rc_dict["Image"]
        rc.resources["Font"] = rc_dict["Font"]
        rc.resources["Sound"] = rc_dict["Sound"]

        resource_categories.append(rc)
    return resource_categories

def parse_unmatched_to_resource_categories(unmatched: List[Dict[str, str]]) -> List[ResourceCategory]:
    resource_categories: List[ResourceCategory] = []

    tmp_cats: Dict[str, ResourceCategory] = {}

    for item in unmatched:
        if item["ResourceCategory"] not in tmp_cats:
            rc = ResourceCategory()
            rc.name = item["ResourceCategory"]
        else:
            rc = tmp_cats[item["ResourceCategory"]]

        if item["ResourceType"] == "Image":
            rc.resources["Image"].append({
                "id": item["ResourceID"],
                "path": item["ResourcePath"]
            })
        elif item["ResourceType"] == "Sound":
            rc.resources["Sound"].append({
                "id": item["ResourceID"],
                "path": item["ResourcePath"]
            })
        elif item["ResourceType"] == "Font":
            rc.resources["Font"].append({
                "id": item["ResourceID"],
                "path": item["ResourcePath"]
            })

        tmp_cats[item["ResourceCategory"]] = rc

    for name, rc in tmp_cats.items():
        resource_categories.append(rc)
    return resource_categories

def get_rc_from_list_by_name(rc_list: List[ResourceCategory], name: str) -> Union[ResourceCategory, None]:
    for rc in rc_list:
        if rc.name == name:
            return rc
    return None

def swap_paths(full_rc_list: List[ResourceCategory], path_rc_list: List[ResourceCategory]):
    for path_rc in path_rc_list:
        orig_rc = get_rc_from_list_by_name(full_rc_list, path_rc.name)
        if orig_rc is None:
            print(f"Resource category {path_rc.name} not found in full resource list.")
            continue

        for rc_cat in orig_rc.resources.keys():
            for correct_path_dict in path_rc.resources[rc_cat]:
                for i in range(len(orig_rc.resources[rc_cat])):
                    if correct_path_dict["id"] == orig_rc.resources[rc_cat][i]["id"]:
                        orig_rc.resources[rc_cat][i]["path"] = correct_path_dict["path"]

def main():
    args = argument_parser()
    args = argument_validator(args)

    res_cat_list = parse_data(parse_xml(args.input_file))

    swap_paths(res_cat_list, parse_data_to_resource_categories(parsed_resources))
    swap_paths(res_cat_list, parse_unmatched_to_resource_categories(unmatched_resources))

    with open(args.output, "w") as f:
        json.dump([rc.get_json() for rc in res_cat_list], f, indent=4)

if __name__ == "__main__":
    main()
