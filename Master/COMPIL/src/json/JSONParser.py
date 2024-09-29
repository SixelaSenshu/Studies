import json
from src.json.JSONObject import JSONObject

class JSONParser:

    def __init__(self, json_file):
        self.json_file = json_file
        self.data = ""
        self.JSONObj = JSONObject()

    def get_json_file(self):
        return self.json_file

    def parse(self):
        with open(self.json_file) as f:
            data = json.load(f)
            self.JSONObj.setType(data["type"])
            self.JSONObj.setProgram(data["program"])
        return data
    
    def print_data(self):
        print(self.JSONObj.getType())
        print(self.JSONObj.getProgram())
        return 0
    
    