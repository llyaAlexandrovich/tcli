import os
import shutil
import glob
import logging
import time
import threading
import requests


# TODO: COMPILED flag in blob files is useless for now since we don't
# TODO: really resolving any dependencies.




def Ping(response: list):
    try:
        logging.info("Establishing internet connection")
        logging.info("Checking github.com availability")
        response[0] = requests.get(url="https://github.com/llyaAlexandrovich/tcli", timeout=20).status_code
    except:
        logging.error("HTTP error occurred. Unable to connect to the remote server")



def RunBlob(FileName: str,
            BlobInfo: list):
    logging.info(f"Trying to run blob - {FileName}")
    logging.info(f"Change working directory to - {os.path.dirname(FileName)}")
    os.chdir(os.path.dirname(FileName))


    logging.info("Clonning external repository")
    os.system(f"git clone {BlobInfo[1]["LINK"]} --depth 1")

    # TODO: We don't check whether these values is already in config or not so they will be
    # TODO: written every time. NOTE: Not REwritten. Just written.
    logging.info(f"BLOB_SOURCE_DIRECTORY={os.path.dirname(FileName)}\\{BlobInfo[1]["NAME"]}")
    logging.info(f"BLOB_BIN_DIRECTORY={os.path.dirname(FileName)}\\{BlobInfo[1]["NAME"]}\\build")
    with open(f"{BlobInfo[1]["NAME"]}.conf", 'a', encoding="utf-8") as f:
        f.write(f"BLOB_SOURCE_DIRECTORY={os.path.dirname(FileName)}\\{BlobInfo[1]["NAME"]}\nBLOB_BIN_DIRECTORY={os.path.dirname(FileName)}\\{BlobInfo[1]["NAME"]}\\build")


    logging.info("Start building process")

    logging.info(f"Change working directory to - {os.path.dirname(FileName)}\\{BlobInfo[1]["NAME"]}")
    os.chdir(f"{os.path.dirname(FileName)}\\{BlobInfo[1]["NAME"]}")


    logging.info("Creating required directories - build")
    try:
        os.mkdir("build")
    except:
        pass


    logging.info(f"Change working directory to - {os.path.dirname(FileName)}\\{BlobInfo[1]["NAME"]}\\build")
    os.chdir(f"{os.path.dirname(FileName)}\\{BlobInfo[1]["NAME"]}\\build")


    logging.info("Executing commands")

    logging.info("cmake -G \"MinGW Makefiles\" ..")
    os.system("cmake -G \"MinGW Makefiles\" ..")

    logging.info("cmake --build . --parallel 8")
    os.system("cmake --build . --parallel 8") # TODO: Number of cores may vary from system to system. This number needs to be reconsidered and automatically changed.


    logging.info("Copying files")
    logging.info("Copying bins to - thirdparty/lib")
    bins = str(BlobInfo[1]["BIN"]).split(' ')
    for bin in bins: 
        shutil.copy(bin, "..\\..\\..\\lib\\")


    logging.info(f"Change working directory to - {os.path.dirname(FileName)}\\{BlobInfo[1]["NAME"]}\\include\\{BlobInfo[1]["NAME"]}")
    os.chdir(f"{os.path.dirname(FileName)}\\{BlobInfo[1]["NAME"]}\\include")
    logging.info(f"Copying includes to - thirdparty\\include{BlobInfo[1]["NAME"]}")
    shutil.copytree(f"{BlobInfo[1]["NAME"]}", f"..\\..\\..\\include\\{BlobInfo[1]["NAME"]}")



def RunBlobs(BlobsInfo: dict,
            BlobFileNames: list):
    logging.info("Create required directories - thirdparty/include thirdparty/lib")
    try:
        os.mkdir("thirdparty/include")
        os.mkdir("thirdparty/lib")
    except:
        pass

    # As long as internet connection is required we checking
    # for it first.
    logging.info("Checking internet connection")

    response = [None]
    threading.Thread(target=Ping, args=[response]).start()


    # Counting server timeout. Drop task if server is not responding.
    TimeStart = time.time()
    while response[0] == None:
        if (time.time() - TimeStart) >= 30:
            logging.critical("Unable to connect to the remote server")
            logging.error("Server timeout reached")
            logging.info("Check your internet connection and try again")
            logging.critical("Unable to satisfy dependencies")
            return


    logging.info("Internet connection established")
    logging.info("Trying to run blobs")

    # Running blobs one by one until all the dependencies resolved.
    for FileName in BlobFileNames:
        if BlobsInfo[FileName][0] == True:
            RunBlob(FileName, BlobsInfo[FileName])



def ResolveBlob(version: str,
                BlobFileName: str):
    # Initial log for blob.
    logging.info(f"Start resolving blob - {BlobFileName}")


    # Checking for blob config file.
    logging.info("Checking for blob config")


    # TODO: Sooner or later i will need to optimize it cause we cannot
    # TODO: run this function again and again for every single absent version
    # TODO: in blobs config.
    CompilationRequired = True
    # If blob configuration absent write the default one.
    if not os.path.exists(f"{os.path.dirname(BlobFileName)}\\{os.path.basename(BlobFileName)[1:]}.conf"):
        logging.info("Config not found")
        logging.info(f"Creating config for blob - {os.path.basename(BlobFileName)[1:]}")
        logging.info(f"Config directory - {os.path.dirname(BlobFileName)}")
        logging.info(f"Config file name - {os.path.dirname(BlobFileName)}\\{os.path.basename(BlobFileName)[1:]}.conf")
        with open(f"{os.path.dirname(BlobFileName)}\\{os.path.basename(BlobFileName)[1:]}.conf", 'w', encoding="utf-8") as f:
            f.write(f"DEPMANAGER_VERSION={version}\rBLOB_FILE_NAME={BlobFileName}\rCOMPILED={False}\n")
    # If blob is already configured(config file exists) check config's depmanager version
    # with current depmanager version and if not equal create new config and delete the old one.
    else:
        logging.info("Config found")
        logging.info("Checking existed config")
        with open(f"{os.path.dirname(BlobFileName)}\\{os.path.basename(BlobFileName)[1:]}.conf", 'r', encoding="utf-8") as f:
            lines = f.readlines()
            for line in lines:
                StringContent = line.strip().split('=')
                match StringContent[0]:
                    case "DEPMANAGER_VERSION":
                        if StringContent[1] != version:
                            logging.warning(f"The versions differ in config - {os.path.dirname(BlobFileName)}\\{os.path.basename(BlobFileName)[1:]}.conf")
                            logging.info("Force program to renew config for current version")
                            logging.info("Removing existed config file")
                            f.close()
                            os.remove(f"{os.path.dirname(BlobFileName)}\\{os.path.basename(BlobFileName)[1:]}.conf")
                            ResolveBlob(version, BlobFileName)
                    case "COMPILED":
                        if StringContent[1] != "True":
                            logging.info(f"Compilatioin required for blob - {os.path.basename(BlobFileName)}")
                        else:
                            logging.info(f"Compilation is not required for blob - {os.path.basename(BlobFileName)}")
                            CompilationRequired = False


    if CompilationRequired:
        logging.info(f"Resolving blob - {BlobFileName}")

        # Resolving blob itself.
        FileContent = {}
        with open(BlobFileName, 'r', encoding="utf-8") as f:
            lines = f.readlines()
            for line in lines:
                StringContent = line.strip().split('=')
                FileContent[StringContent[0]] = StringContent[1]

        logging.info("Blob's info")
        logging.info(f"Blob's name - {FileContent["NAME"]}")
        logging.info(f"Blob's link - {FileContent["LINK"]}")
        logging.info(f"Blob's dependencies - {FileContent["DEPS"]}")
        logging.info(f"Blob's dependent - {FileContent["OTHERS_DEP"]}")
        logging.info(f"Blob's generator - {FileContent["GEN"]}")
        logging.info(f"Blob's compilation script - {FileContent["SCRIPT"]}")
        logging.info(f"Blob's bins - {FileContent["BIN"]}")
        logging.info(f"Blob's includes - {FileContent["INCLUDE"]}")

        # Output value contains all data collected from blob.
        output = [CompilationRequired, FileContent] # [CompilationRequired(True|False){FileContent(dict)}]

        return output
    return [False]



def ResolveBlobs(version: str):
    logging.info("Trying to resolve blobs")

    # This values is initial and required for blobs processing not blobs tasking.
    BlobFileNames = [] # Full path to every known blob file founded.
    BlobsInfo     = {} # [BlobFileNames[]][""] like dictionary.


    logging.info("Searching for blobs")

    # Go through special directory(thirdparty) and search for
    # @blob files.
    for file in glob.glob("thirdparty\\**\\@*"):
        logging.info(f"Blob file found - {os.path.abspath(file)}")
        BlobFileNames.append(os.path.abspath(file))
    
    logging.info("Trying to resolve blobs")

    # Run blobs.
    for FileName in BlobFileNames:
        BlobsInfo[FileName] = ResolveBlob(version, FileName)


    return BlobsInfo, BlobFileNames



def InitDepManager(version: str):
    # Init logging from parent process.
    logging.getLogger("root")
    logging.info("Logger inherited successfully")


    # Get abspath.
    CurrentDirectory = os.path.abspath('.')
    logging.info(f"Current directory - {CurrentDirectory}")


    # Resolving and running blobs.
    BlobsInfo, BlobFileNames = ResolveBlobs(version)
    RunBlobs(BlobsInfo, BlobFileNames)
