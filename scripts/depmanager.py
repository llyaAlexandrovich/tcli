import os
import sys
import glob
import pathlib
import logging
import time
import threading
import requests






def Ping(response: list[requests.Response]):
    try:
        logging.info("Establishing internet connection")
        logging.info("Checking github.com availability")
        response[0] = requests.get(url="https://github.com/llyaAlexandrovich/tcli", timeout=20)
    except:
        logging.error("HTTP error occurred. Unable to connect to the remote server")



def RunBlob(BlobInfo: dict,
            BlobName: str):
    logging.info(f"Trying to run blob - {BlobInfo[BlobName]["NAME"]}")
    logging.info("Sheduling tasks")



def RunBlobs():
    pass



def ResolveBlob():
    pass



def ResolveBlobs():
    # This values is initial and required for blobs processing not blobs tasking.
    BlobFileNames = [] # Full path to every known blob file founded.
    BlobsInfo     = {} # [BlobFileNames[]][""] like dictionary.


    logging.info("Searching for blobs")

    # Go through special directory(thirdparty) and search for
    # @blob files.
    for file in glob.glob("thirdparty\\**\\@*"):
        logging.info(f"Blob file found - {os.path.abspath(file)}")
        BlobFileNames.append(os.path.abspath(file))


    logging.info("Checking for blobs config")

    # Check for $(blobName).conf file in every directory where
    # blob files were found.
    for FileName in BlobFileNames:
        pass




def InitDepManager(version: str):
    # Init logging from parent process.
    logging.getLogger("root")
    logging.info("Logger inherited successfully")


    # Get abspath. NOTE: there's no reason to do so yet.
    CurrentDirectory = os.path.abspath('.')
    logging.info(f"Current directory - {CurrentDirectory}")


    # TODO: THIS CODE DOWN THERE IS SIMPLY AWFULL. REWRITE IT. ---------


    # Iterate through thirdparty directory and find all the
    # blob(@filename) files.
    logging.info("Searching for blobs")
    BlobInfo  = {}
    BlobTasks = {}
    BlobFiles = []

    for file in glob.glob("thirdparty\\**\\@*"):
        logging.info(f"Blob file found - {os.path.abspath(file)}")
        BlobFiles.append(os.path.abspath(file))


    logging.info("Extracting info from blobs")


    # Getting info from blobs.
    for file in BlobFiles:
        FileContent = {}
        # Reading data from blobs.
        with open(file, 'r', encoding="utf-8") as f:
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
        logging.info(f"Blob's compile script - {FileContent["SCRIPT"]}")


        # Creating .conf file for every blob so we could skip
        # any already processed steps. Configs are created only
        # if there's none already.
        if not os.path.exists(f"{os.path.dirname(file)}\\{FileContent["NAME"]}.conf"):
            logging.info(f"Creating config for blob - {FileContent["NAME"]}")
            logging.info(f"Config directory - {os.path.dirname(file)}")
            logging.info(f"Config file name - {os.path.dirname(file)}\\{FileContent["NAME"]}.conf")
            with open(f"{os.path.dirname(file)}\\{FileContent["NAME"]}.conf", 'w', encoding="utf-8") as f:
                f.write(f"DEPMANAGER_VERSION={version}\rBLOB_FILE_NAME={file}\rCONFIGURED={False}\rCOMPILED={False}")
        else:
            with open(f"{os.path.dirname(file)}\\{FileContent["NAME"]}.conf", 'r', encoding="utf-8") as f:
                lines = f.readlines()
                for line in lines:
                    StringContent = line.strip().split('=')
                    match StringContent[0]:
                        case "DEPMANAGER_VERSION":
                            if StringContent[1] != version:
                                logging.warning(f"Versions diverge")
                                logging.info("Force program to renew configs for current version")
                                logging.info("Removing existed config files")
                                break
                                
                    break
            
            # Remove old config file 
            os.remove(f"{os.path.dirname(file)}\\{FileContent["NAME"]}.conf")
                                

        

        BlobInfo[file] = FileContent
        BlobTasks[file] = False


    # TODO: ----------------------------------------------------------------

    
    logging.info("Trying to run blobs")
    
    # Running blobs.
    # Trying to find blobs with no dependencies and run them first.
    while True:
        for blob in BlobTasks:
            if BlobTasks[blob] == False:
                if BlobInfo[blob]["DEPS"] == "":
                    # Checking internet connection.
                    # Try ping required servers.
                    response = [None]
                    thread = threading.Thread(target=Ping, args=[response]).start()

                    # Counting server timeout. Drop task if server not responding.
                    TimeStart = time.time()
                    while response[0] == None:
                        if (time.time() - TimeStart) >= 30:
                            logging.error("Server timeout reached")
                            logging.critical("Unable to satisfy dependencies")
                            return
    

                    # Server is up and running.
                    logging.info("Server connection established")
                    
                    # Running current blob.
                    RunBlob(BlobInfo, blob)


        break
        
        
    
