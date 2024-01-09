class Car:
    def __init__(self, _number, _make, _model, _price) -> None:
        self.__number = _number
        self.__make = _make
        self.__model = _model
        self.__price = _price
    
    def get_vehicle_name(self):
        return self.__make + " " + self.__model
    
    def display(self):
        print("License #: {}\n\
Vehicle Name: {}\n\
Price: {}".format(self.__number, self.get_vehicle_name(), self.__price))
        
car = Car(5593516, "B.M.W", "E46", 40000)
car.display()