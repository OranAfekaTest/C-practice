import ui

rooms = ("Room0", "Room1", "Room2", "Room3", "Room4", "Room5", "Room6", "Room7")
participents = ("Izik" ,"Munther", "Sahar", "Ron", "Ofir", "Din", "Rasheed", "Neta", "Amir", "Shoham")

    
#def create_meeting(_name, _start, _end, _room, _participents):
#    if _end - _start < 15:
#        pass
#    res = {"name": _name, "start": _start, "end": _end, "room": _room, "participents": _participents}
#    return res

def start():
    meetings = []
    ui.print_meetings(meetings)
    choice = ui.main_menu()
    if(choice == 1):
        ui.create_meeting()

if __name__ == "__main__":
    start()