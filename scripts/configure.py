import os
import sys
import logging
import requests


from dotenv import dotenv_values
from depmanager import InitDepManager


global version
version = "1.0.0"



if __name__ == "__main__":
    # Normalize working directory to work from.
    CurrentPath = os.getcwd()

    if "scripts" in CurrentPath:
        os.chdir("..")
        CurrentPath = os.getcwd()


    # Create .env file with initial values from .env.global .
    EnvGlobal = open(".env.global")
    with open(".env", 'w', encoding="utf-8") as f:
        f.write(EnvGlobal.read())
    EnvGlobal.close()


    # Add some machine dependent variables in .env .
    with open(".env", 'a', encoding="utf-8") as f:
        f.write(f"\nOS={os.name}\n")


    # Get environment variables.
    env = dotenv_values(".env")
    PathEnv = os.environ["PATH"]
    PathEnvDict = PathEnv.split(';')
    

    # Initialize logging.
    logging.basicConfig(format="%(asctime)s - %(filename)s - %(levelname)s - %(message)s",
                        datefmt="%Y-%m-%d %H:%M:%S%z",
                        level=env["LOGGING_LEVEL"],
                        encoding="utf-8",
                        handlers=[
                            logging.StreamHandler(sys.stdout),
                            logging.FileHandler("temp/configure.log", mode='a')
                        ])


    logging.info("Logging initialized successfully")
    logging.info("Logging file - temp/configure.log")
    logging.info(f"Operating system detected - {env["OS"]}")
    logging.info(f"Project version - {env["VERSION"]}")
    logging.info(f"Default logging level - {env["LOGGING_LEVEL"]}")


    # Checking if current version is the newest.
    try:
        response = requests.get("https://raw.githubusercontent.com/llyaAlexandrovich/tcli/refs/heads/main/.env.global", timeout=3)
        if response.status_code == 200:
            logging.info("Get data from remote repositoy - https://github.com/llyaAlexandrovich/tcli")
            logging.info("Creating temporary file in - temp/")
    
            with open("temp/.env.temp", 'w', encoding="utf-8") as TempEnv:
                TempEnv.write(response.text)
    
            logging.info("Temporary file name - .env.temp")
    
            RemoteEnv = dotenv_values("temp/.env.temp")
    
            if RemoteEnv["VERSION"] != env["VERSION"]:
                logging.info("Newly version available. Consider updating")
            else:
                logging.info("Current version considered newest")
        else:
            logging.warning("Unable to fetch data from official repository. Recommend to update manually")
    except:
        logging.error("HTTP error occurred. Unable to fetch from remote repository")
        logging.warning("Unable to determine whether the newest version is used")
        logging.warning("Version fetching skipped")
    


    # Check internal required dependencies.
    if "mingw" and "cmake" not in PathEnv.lower():
        logging.critical("Lack of dependencies")
        logging.critical("GCC-14, G++-14, git and CMake-4.2 required to build this project. Doxygen and mkdocs might also be used but not strictly required")
        logging.info("If required dependencies are installed try specify them using .env file and restart the program")
        exit()


    # Add additional requried data to .env .
    logging.info("Add dependencies data to the .env")
    if env["OS"] == "nt":
        for arg in PathEnvDict:
            if "mingw" in arg:
                logging.info("Add gcc absolute path")
                logging.info("Add gxx absolute path")
                with open(".env", 'a', encoding="utf-8") as f:
                    f.write(f"GCC={arg}\\gcc.exe\n")
                    f.write(f"GXX={arg}\\g++.exe\n")
            if "cmake" in arg.lower():
                    logging.info("Add cmake absolute path")
                    with open(".env", 'a', encoding="utf-8") as f:
                        f.write(f"CMAKE={arg}\\cmake.exe\n")
            if "git" in arg.lower():
                logging.info("Add git absolute path")
                with open(".env", 'a', encoding="utf-8") as f:
                    f.write(f"GIT={arg}\\git.exe\n")
    # TODO: Linux part is still not done yet.
    #elif env["OS"] == "posix":
    #    pass


    # Resolving dependencies.
    logging.info("Start resolving dependencies")
    InitDepManager(version)
