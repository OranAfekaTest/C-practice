from calendar import day_name
from datetime import datetime

def main_menu():
    print("1) Create new meeting\n \
           2) Search existing meeting\n \
           3) Delete meeting\n \
           4) Save Diary\n \
           5) Load Diary\n \
           6) Exit")
    while(True):    
        try:
            choice = int(input())
            if choice not in range(1,7):
                raise ValueError
            return choice
        except Exception:
            print("you must choose a number between 1 and 6.")

def print_meetings(meetings):
    print([day_name[(i+6)%7] for i in range(5)])
    for i in range(6):
        if i:
            day = day_name[(i+5)%7]
        else:
            day =""
        print("{0:^12}|".format(day), end="")

def create_meeting(rooms, participents):
    print("Please enter meeting's details, press q to quit")
    name = input("name: ")
    invalid_input = True
    print("Date entry format yyyy,mm,dd,hh,mm")
    while invalid_input:
        try:
            start = input("start date and time: ")
            start = tuple(int(x) for x in start.split(','))
            print(start)
            start = datetime(start[0], start[1], start[2], start[3], start[4], 0)
            if start < datetime.now():
                raise PastDateError
            if start[3] < 9 or 17 < start[3] or (start[3] == 17 and 45 < start[4]):
                raise OutOfScopeError
            print(start)
            invalid_input = False
        except PastDateError:
            print("meeting date can't be in the past")
        except OutOfScopeError:
            print("meetings can be schedualed between 9:00 and 18:00")
        except Exception:
            print("please enter the date and time according to format above")
    invalid_input = True

    while invalid_input:
        try:
            end = input("end time (hh,mm): ")
            end = tuple(int(x) for x in end.split(','))
            print(start)
            start = datetime(start[0], start[1], start[2], end[3], end[4], 0)
            if end[3] < 9 or 17 < end[3]:
                raise OutOfScopeError
            if end - start < 15:
                raise ShortMeetError
            print(end)
            invalid_input = False
        except ShortMeetError:
            print("meeting is too short, minimum duration is 15 min.")
        except OutOfScopeError:
            print("meetings can be schedualed between 9:00 and 18:00")
        except Exception:
            print("please enter the date and time according to format above")
    
    
    res = {"name": name, "start": start, "end": end, "room": room, "participents": participents}
    return res

class PastDateError(Exception):
    pass 

class ShortMeetError(Exception):
    pass

class OutOfScopeError(Exception):
    pass