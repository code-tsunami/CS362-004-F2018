import random

firstPart = [
	{"string": "ftp://", "isValid": True},
	{"string": "h3t://", "isValid": True},
	{"string": "3ht://", "isValid": False},
	{"string": "http:/", "isValid": False},
	{"string": "http://", "isValid": True},
	{"string": "https://", "isValid": True},
	{"string": "http:", "isValid": False},
	{"string": "://", "isValid": False},
	{"string": "http/", "isValid": False},
	{"string": "", "isValid": True}
]

secondPart = [
	{"string": "www.google.com", "isValid": True},
	{"string": "oregonstate.edu", "isValid": True},
	{"string": "docs.python.org", "isValid": True},
	{"string": "europa.eu", "isValid": True},
	{"string": "0.0.0.0", "isValid": True},
	{"string": "255.255.255.255", "isValid": True},
	{"string": "256.255.255.255", "isValid": False},
	{"string": "255.com", "isValid": True},
	{"string": "1.2.3.4.5", "isValid": False},
	{"string": "1.2.3.4.", "isValid": False},
	{"string": "1.2.3", "isValid": False},
	{"string": ".1.2.3.4", "isValid": False},
	{"string": "site.z9", "isValid": False},
	{"string": "nodomain", "isValid": False},
	{"string": "", "isValid": False}
]

thirdPart = [
	{"string": ":65535", "isValid": True},
	{"string": ":1024", "isValid": True},
	{"string": "", "isValid": True},
	{"string": ":-1", "isValid": False},
	{"string": ":65536", "isValid": False},
	{"string": ":65a", "isValid": False}
]

fourthPart = [
	{"string": "/456", "isValid": True},
	{"string": "/z456", "isValid": True},
	{"string": "/..", "isValid": False},
	{"string": "/../", "isValid": False},
	{"string": "/../", "isValid": False},
	{"string": "/..//login", "isValid": False},
	{"string": "/admin//login", "isValid": False},
	{"string": "/admin/", "isValid": True},
	{"string": "", "isValid": True},
	{"string": "/path#index", "isValid": True},
	{"string": "/admin/login?admin=false", "isValid": True},
	{"string": "/admin/login", "isValid": True},
	{"string": "?q=Test%20URL-encoded%20stuff", "isValid": True}
]

f_valid = open("validUrls", "w")
f_invalid = open("invalidUrls", "w")

for i in range(0, 1000):
	first = random.choice(firstPart)
	second = random.choice(secondPart)
	third = random.choice(thirdPart)
	fourth = random.choice(fourthPart)
	f = f_valid
	if(not first["isValid"] or not second["isValid"] or not third["isValid"] or not fourth["isValid"]):
		f = f_invalid
	url = first["string"] + second["string"] + third["string"] + fourth["string"]
	f.write("\"{}\",\n".format(url))
