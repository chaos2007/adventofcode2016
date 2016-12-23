import unittest
import re

def calculate_checksum(room_name):
    name = room_name.replace("-", "")
    count = {}
    for x in name:
        count[x] = count[x] + 1 if x in count else 1
    count = [k for k, v in sorted(count.iteritems(), key=lambda(k,v): (-v,k))]
    return "{}{}{}{}{}".format(count[0], count[1], count[2], count[3], count[4])

def count_valid_rooms(rooms):
    count = 0
    for room in rooms.splitlines():
        room = room.lstrip().rstrip()
        match = re.match( r'(.*)-(.*)\[(.*)\]', room, re.M|re.I)
        name, number, checksum = match.group(1), match.group(2), match.group(3)
        room_checksum = calculate_checksum(name)
        if checksum == room_checksum:
            count += int(number)
    return count

def decipher_character(character, rot_number):
    if character == '-': return ' '
    return chr((((ord(character)-97) + rot_number)%26) + 97)

def decipher_room_name(room_name):
    room_name = room_name.lstrip().rstrip()
    match = re.match( r'(.*)-(.*)\[(.*)\]', room_name, re.M|re.I)
    name, number, checksum = match.group(1), match.group(2), match.group(3)
    number = int(number)
    name = map((lambda x: decipher_character(x, number)), name)
    return ("".join(name), number)

def decipher_rooms(rooms):
    rooms = map((lambda x: decipher_room_name(x)), rooms.splitlines())
    rooms = dict(rooms)
    return rooms 

class MyTest(unittest.TestCase):
    def test_1(self):
        self.assertEquals("abxyz", calculate_checksum("aaaaa-bbb-z-y-x"))
    def test_2(self):
        self.assertEquals("abcde", calculate_checksum("a-b-c-d-e-f-g-h"))
    def test_3(self):
        self.assertEquals("oarel", calculate_checksum("not-a-real-room"))
    def test_4(self):
        self.assertNotEquals("decoy", calculate_checksum("totally-real-room"))
    def test_5(self):
        rooms = """aaaaa-bbb-z-y-x-123[abxyz]
        a-b-c-d-e-f-g-h-987[abcde]
        not-a-real-room-404[oarel]
        totally-real-room-200[decoy]"""
        self.assertEquals(1514, count_valid_rooms(rooms))

    def test_6_decypher(self):
        (room_name, _) = decipher_room_name("qzmt-zixmtkozy-ivhz-343[abcdef]")
        self.assertEquals("very encrypted name", room_name)

    def test_part_1(self):
        with open("input.txt", 'r') as content_file:
            rooms = content_file.read()
            self.assertEquals(185371, count_valid_rooms(rooms))

    def test_part_2(self):
        with open("input.txt", 'r') as content_file:
            rooms = content_file.read()
            rooms = decipher_rooms(rooms)
            self.assertEquals(984, rooms['northpole object storage'])

if __name__ == '__main__':
    unittest.main()


