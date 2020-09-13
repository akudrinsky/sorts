#!/Library/Frameworks/Python.framework/Versions/3.8/bin/python3

Configs = {
    "filename": "data/tests.txt",
    "length": {
        "start": 5,
        "end": 1000,
        "step": 50
    },
    "n_cases": 20,
    "values": {
        "min": 0,
        "max": 10 ** 3
    }
}

import random
import sys

def makeTest(file, testSize):
    """
    Writes test array of a given size to a file in a form "length: num_1 num_2 ... num_length"
    """
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
        