import sys
import image-recognition.classify_image as classify_image

def user(arg):
    ans=True
    while ans:
        print ("""
        1.Reconize image
        2.something else
        3.Something else
        4.Exit/Quit
        """)
        ans=raw_input("What would you like to do? ")
        if ans=="1":
            imagerecog(image)
          print("\n Student Added")
        elif ans=="2":
          print("\n Student Deleted")
        elif ans=="3":
          print("\n Student Record Found")
        elif ans=="4":
          print("\n Goodbye")
        elif ans !="":
          print("\n Not Valid Choice Try again")


def imagerecog(arg):
    pass
    classify_image.main().
