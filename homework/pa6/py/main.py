import sys

def encodeFile(file_name):
   pass

def decodeFile(file_name):
   pass

def main():
   if len(sys.argv) != 3:
      print("Expected format: PA6.py <encode / decode> <file_name>")
      return

   if sys.argv[1] == "encode":
      #encode ABC.txt to ABC.txt.coded
      encodeFile(sys.argv[2])
      print("File", sys.argv[2], "encoded.")

   elif sys.argv[1] == "decode":
      #decode ABC.txt.coded to ABC.decoded.txt
      decodeFile(sys.argv[2])
      print("File", sys.argv[2] , "decoded.")
   else:
      print("Unexpected command.")

if __name__ == '__main__':
   main()
