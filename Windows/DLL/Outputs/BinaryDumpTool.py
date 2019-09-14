# Python 3+ is required to run this script and also dumpbin.exe from VS is needed.
# Place this script into same directory as the binary file you are trying to inspect and
# then run this script and the output file (dump.txt) should appear to the same directory location.
import sys
import subprocess

# Location of the needed dumpbin.exe:
# r"C:/Program Files (x86)/Microsoft Visual Studio/2017/Enterprise/VC/Tools/MSVC/14.16.27023/bin/Hostx64/x64/dumpbin.exe"
# r"C:/Program Files (x86)/Microsoft Visual Studio/2017/Professional/VC/Tools/MSVC/14.14.26428/bin/Hostx64/x64/dumpbin.exe"
DUMPBIN = r"C:/Program Files (x86)/Microsoft Visual Studio/2019/Enterprise/VC/Tools/MSVC/14.22.27905/bin/Hostx64/x64/dumpbin.exe"
OUTPUT_FILE = "dump.txt"

def writeToFile(cmd):
    with open(OUTPUT_FILE, "w") as outfile:
        subprocess.call(cmd, stdout=outfile)
    print(OUTPUT_FILE, "was created successfully.")
    input()

def main():
    print(sys.version); print('')
    print("What do you want to do with a binary file?")
    print("[1] List dependencies")
    print("[2] List exported functions")
    print("[3] List everything possible about the DLL")
    choice = input()

    if choice == '1':
        dll = input("What is the full name of the dll file?\n")
        cmd = [DUMPBIN, dll, "/dependents"]
    elif choice == '2':
        dll = input("What is the full name of the dll file?\n")
        cmd = [DUMPBIN, dll, "/EXPORTS"]
    elif choice == '3':
        dll = input("What is the full name of the dll file?\n")
        cmd = [DUMPBIN, dll, "/ALL"]
    else:
        print("\nUsage:")
        print("Place this file into same directory as the file you are trying to inspect "\
              "and then hope that your dumpbin.exe exists in the hardcoded path:", DUMPBIN)
        print("Then follow the script directions and dump.txt should appear to current directory location") 
        input()
        return
    
    writeToFile(cmd)

main()