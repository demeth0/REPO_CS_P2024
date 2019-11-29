a = int(input("Veuillez entrer le premier nombre : \t"))
b = int(input("Veuillez entrer le deuxième nombre : \t"))


def PGCD (a,b):
    if (b == 0) :
        print ("Le pgcd de", a, "et de", b, "est", a )
    elif (a == 0) :
        print ("Le pgcd de", a, "et de", b, "est" ,b )
    elif (b!= 0 and a!=0):

                    r = int(a%b)
                    while (r!=0):
                        r = int(a%b)
                        a=b
                        b= r

                    print("le pgcd est", a)


PGCD (a,b)
