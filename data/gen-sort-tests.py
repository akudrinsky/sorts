#!/Library/Frameworks/Python.framework/Versions/3.8/bin/python3

Configs = {
    "filename": "data/tests.txt",
    "length": {
        "start": 10,
        "end": 1000,
        "step": 10
    },
    "n_cases": 50,
    "values": {
        "min": 0,
        "max": 10 ** 6
    }
}

import random
import sys

def makeTest(file, testSize):
    data = [random.randint(Configs["values"]["min"], Configs["values"]["max"]) for i in range(testSize)]
    file.write(str(testSize) + ": ")
    file.write(" ".join(str(number) for number in data))
    file.write("\n")

if __name__ == "__main__":
    try:
        print("INFO >>> generating tests!")
        resultFile = open(Configs["filename"], "w")

        for testSize in range(Configs["length"]["start"], 
                            Configs["length"]["end"], Configs["length"]["step"]):
            for case in range(Configs["n_cases"]):
                makeTest(resultFile, testSize)

            print("INFO >>> size {} was successfully generated".format(testSize))
        
        resultFile.close()
        print("INFO >>> tests are ready!")
    except:
        print("ERROR >>> unknown error while generating tests: ", sys.exc_info()[0])
        