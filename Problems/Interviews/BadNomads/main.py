# python 3.8.2

import requests
import json

# response = requests.get("https://api.trello.com/1/members/me/boards?key={b6a905dd62f26c99fcbcf48aeb374572}&token={f2ad4e3bedec57450b6a851747ad05ef8b50fea1fada93ea5b0e620b42be7757}")
# print(response.headers)


# read file
with open('response.json', 'r') as myfile:
    data=myfile.read()

# parse file
obj = json.loads(data)

# show values
print( str(obj[0]))



