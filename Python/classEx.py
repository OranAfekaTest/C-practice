import re
#print("please enter your surename:")
#sureName = input()
#print("please enter your firstname:")
#firstName = input()
#print("welcome", firstName, sureName)

#num = int(input)
#dig1 = num%10
#dig2 = num/10%10
#dig3 = num/100
#print(dig1 + dig2 +dig3)

#user = input("enter user name:")
#if user == "admin":
#    password = input("enter user password:")
#    if password == "TheMaster":
#        print("Welcome!")
#    elif password == "cancel":
#        print("Cancelled.")
#    else:
#        print("wrong password")
#elif user == "cancel":
#        print("Cancelled.")
#else:
#    print("wrong user name")

#num = int(input("Enter a number:"))
#digSum = 0
#while 0 < num:
#    digSum += num%10
#    num = int(num / 10)
#print("sum of digits:", digSum)

#max = int(input("Enter maximum value for fibonacci sequence:"))
#fib1 = 0
#fib2 = 1
#while(fib2 < max):
#    tmp = fib2
#    fib2 += fib1
#    fib1 = tmp
#    print(fib1, ", ")
#print(fib2)

#num = int(input("enter squre size:"))
#for i in range(num):
#    for j in range(num):
#        print("*", end=" ")
#    print()

#num = input("enter credit card number:")
#lst = []
#for quad in num.split(" "):
#    lst += list(quad)
#lst = [int(x) for x in lst][::-1]
#for n in range(1, len(lst), 2):
#    lst[n] *= 2
#    if 9 < lst[n]:
#        lst[n] = int(lst[n] / 10) + (lst[n] % 10)
#if sum(lst) % 10 == 0:
#    print("valid credit card")
#else:
#    print("invalid number")

#sum = 0
#counter = 0
#while True:
#    num = input("enter number to calc avg, enter Q at the end:")
#    if num == 'Q':
#        break
#    sum += (int(num))
#    counter += 1
#print(sum / counter)

text = """The following address is the first of Huxley’s many talks on the
attainment of visionary experience. Eileen J. Garrett, a longtime friend,
was president of the Parapsychology Foundation which hosted annual
symposia attracting the leading figures in the field. Huxley’s interest in
parapsychology goes back to the 1930s, when he visited Dr J B. Rhine
at Duke University in 1937.
IT IS DIFFICULT to speak of mental events except in similes drawn from the
familiar universe of material things. A man may be said to consist of an Old
World of personal consciousness, and, on the other side of a dividing ocean,
of a series of New Worlds. These New Worlds of a subconscious can never
be colonized, are seldom thoroughly explored, and in many cases await even
discovery. As in this earth, if you go to the antipodes of the. self-conscious
personality, you will encounter all sorts of creatures at least as odd as
kangaroos. We do not, in either case, invent these creatures. They live
independently, and beyond our control. But we may go where they are, and
observe them. They exist “out there” in the mental equivalent of distant
space. From “in here” we can sometimes watch them as they go about their
mysterious business.
Some never consciously discover their antipodes. Others make an
occasional landing. A few others come and go easily at will. For the
naturalist of the mind—who must gather his data before we become true
zoologists of the mind—the primary need is for some safe, easy, reliable
method of transportation between the two Worlds. Two such methods exist.
Neither is perfect; both are sufficiently reliable, easy and safe to justify their
use by those who know what they do. The first is by use of mescalin, analkaloid chemical. The second is by means of hypnotism. The two vessels
carry consciousness to the same region; the drug has longer range and carries
one farther into the terra incognita.
As to hypnosis, we do not know how it produces its observed effects. Nor
need we know. About the physiological effects of mescalin we know a little.
It interferes with the enzyme system regulating cerebral functioning, impairs
the brain’s efficiency and permits entry into consciousness of certain kinds
of mental activity normally excluded as possessing no survival value. We
have visions. But they are not random visions. What takes place in them
follows patterns as logical internally as are the things seen in the antipodes
of the external world. They are strange, but with a certain regularity.
Certain common features are imposed by this pattern upon our visionary
experience. First, and most important, is the experience of light. Everything
is brilliantly illuminated, shining from within, and a riot of colors is
intensified to a pitch unknown in the normal state. (Most normal dreams are
either in black and white or only faintly colored.) Color in dream or vision
probably represents sight of “something given” as distinguished from the
dramatic symbols of our own struggles or wishes, which are usually
uncolored. The visions seen in these antipodes of the mind have nothing to
do with the dreams of normal sleep, which we ourselves generate. We see
them because they are there, but they are not our creations. Such
preternatural light is characteristic of all visionary experience."""

#words = re.split(" |\n", text)
#special_chars = ['!', '?', '"', '\'', ':' ,';', ',', '(', ')', '’', '.', '*', '[', ']', '“', '”']
#wordCount = {}
#for word in words:
#    for c in special_chars:
#        word = word.replace(c, "").lower()
#    if wordCount.get(word, 0) == 0:
#        wordCount[word] = 1
#        wordCount[word] += 1
#print(sorted(wordCount.items(), reverse= True, key= lambda e : e[1]))

#words = ["nap", "teachers", "cheaters", "PAN", "ear", "era", "hectares"]
#for word in words:
#    pass

#def gcd(_a, _b):
#    if(_a == 0):
#        return _b
#    if(_b == 0):
#        return _a
#    print("_a:", _a, "_b:", _b)
#    if(_a < _b):
#        return gcd(_a, _b % _a)
#    else:
#        return gcd(_b, _a % _b)
#print(gcd(1071, 462))
#print(gcd(234, 234234))
#print(gcd(2324, 5234))

#def get_proper_divisors(num):
#    """ get all proper divisors of an integer """
#    result = []
#    for i in range(1, int(num / 2) + 1):
#        if num % i == 0:
#            result.append(i)
#    return result
#
#def is_perfect(num):
#    """ checks whether num is a perfect number or not """
#    if sum(get_proper_divisors(num)) == num:
#        return True
#    else:
#        return False
#
#def find_perfect_numbers(n):
#    """ finds all the perfect numbers which are less than or equal to n """    
#    result = []
#    for i in range(6, n + 1):
#        if(is_perfect(i)):
#            result.append(i)
#    return result
#
#print(find_perfect_numbers(10000))

#def rank(scores):
#    ranks = []
#    scores.sort(reverse  = True) 
#    previous = scores[0] + 1
#    rank = 0
#    for grade in scores:
#        if grade < previous:
#            rank += 1
#        ranks.append(rank)
#        previous = grade
#    return ranks

#scores = [87, 75, 75, 50, 32, 32]
#score_ranks = rank(scores)
#print(score_ranks)

#def list_avg(lst):
#    return sum(lst) / len(lst)

#def calc_grade_avg(student_grades):
#    return {student:list_avg(grades) for student, grades in student_grades.items()}

#student_grades_dict = {"oran": [63, 70, 82, 97, 75], "munther": [87, 75, 78, 70, 92, 32], "sahar": [87, 75, 78, 82, 97, 92]}
#print(calc_grade_avg(student_grades_dict))

def apply(func, lst):
    for n in range(len(lst)):
        lst[n] = func(lst[n])

lst = [1, 2, 3, 4, 5]
apply(lambda x: x * 5, lst)
print(lst)

lst = ["sdf", "Gdeg", "fdf", "fdsASD"]
apply(lambda x: x.capitalize() , lst)
print(lst)
