import argparse
import json
import sys
import os
import subprocess
import shutil

SCRIPT_DIR = os.path.dirname(os.path.realpath(__file__))
BUILD_DIR = os.path.join(SCRIPT_DIR, "build")
BUILD_CACHE_SUBDIR = "cache"

DEFAULT_BUILD_CONFIG_NAME = "build-config.json"
ALLOWED_ACTIONS = ["compile", "upload", "clean"]
ALLOWED_BUILD_TYPES = ["release", "debug"]

currentBuildConfig = None

def parseArgs():
	parser = argparse.ArgumentParser("build",
									 description="Helper script for building the BadgeOS project.")

	parser.add_argument("--gen-config",
						action="store_true",
						help="If specified, generates a sample config file in the working directory.")

	parser.add_argument("--build-config",
						default=DEFAULT_BUILD_CONFIG_NAME,
						help=f"Path to build config. Defaults to {DEFAULT_BUILD_CONFIG_NAME} in the working directory.")

	parser.add_argument("--build-type",
						default=ALLOWED_BUILD_TYPES[0],
						help="Configuration in which to build. Valid values are: " + ", ".join(ALLOWED_BUILD_TYPES))

	parser.add_argument("cmds",
						nargs="*",
						help="Commands to execute. Valid values are: " + ", ".join(ALLOWED_ACTIONS))

	return parser.parse_args()

def validateArgs(args):
	for command in args.cmds:
		if command not in ALLOWED_ACTIONS:
			print(f"Unrecognised command: '{command}'.", file=sys.stderr)
			sys.exit(1)

	if args.build_type not in ALLOWED_BUILD_TYPES:
		print(f"Unrecognised build type: '{args.build_type}'.")
		sys.exit(1)

def createConfigHeader():
	configHeaderPath = os.path.join(SCRIPT_DIR, "src", "BuildAutoGen", "Config.h")
	isDebug = currentBuildConfig["buildType"] == "debug"

	with open(configHeaderPath, "w") as outFile:
		outFile.write("#pragma once\n")
		outFile.write("\n")
		outFile.write("// At the moment there doesn't seem to be a straightforward way of\n")
		outFile.write("// providing custom defines to the build toolchain on the command line,\n")
		outFile.write("// without obliterating the existing config for the board we're building for.\n")
		outFile.write("// Therefore, this header file contains general configuration defines and\n")
		outFile.write("// is generated automatically when build.py is executed.\n")
		outFile.write("// To ensure that compile errors are thrown if this file is not included\n")
		outFile.write("// where it needs to be, things that would normally be done via #ifdef PROP\n")
		outFile.write("// are instead implemented as #if PROP().\n")
		outFile.write("\n")
		outFile.write(f"#define IS_DEBUG() {'true' if isDebug else 'false'}\n")

	print("Created config header:", configHeaderPath)

def initBuildDir(clean=False):
	createBuildDir = False

	if os.path.isfile(BUILD_DIR):
		os.remove(BUILD_DIR)
		createBuildDir = True
	elif not os.path.isdir(BUILD_DIR):
		createBuildDir = True
	elif clean:
		print("Cleaning build directory", BUILD_DIR)
		shutil.rmtree(BUILD_DIR)
		createBuildDir = True

	if createBuildDir:
		os.makedirs(BUILD_DIR)
		os.mkdir(os.path.join(BUILD_DIR, BUILD_CACHE_SUBDIR))

def runProcess(args):
	print("Running command:", " ".join(args))

	result = subprocess.run(args)

	if result.returncode != 0:
		print("Command exited with error code", result, file=sys.stderr)
		sys.exit(1)

	print("Command executed successfully.")

def compile():
	createConfigHeader()

	args = \
	[
		currentBuildConfig["arduinoCliPath"],
		"compile",
		"--build-path",
		BUILD_DIR,
		"--build-cache-path",
		os.path.join(BUILD_DIR, BUILD_CACHE_SUBDIR),
		"--fqbn",
		currentBuildConfig["fqbn"],
		"--warnings",
		"all",
		SCRIPT_DIR
	]

	runProcess(args)

def upload():
	args = \
	[
		currentBuildConfig["arduinoCliPath"],
		"upload",
		"-t",
		"--fqbn",
		currentBuildConfig["fqbn"],
		SCRIPT_DIR
	]

	runProcess(args)

def generateSampleBuildConfig():
	defaultConfig = \
	{
		"arduinoCliPath": "path/to/arduino-cli.exe",
		"fqbn": "board:name:string"
	}

	with open(DEFAULT_BUILD_CONFIG_NAME, "w") as outFile:
		json.dump(defaultConfig, outFile)

	print("Wrote sample build config to", DEFAULT_BUILD_CONFIG_NAME)

def loadBuildConfig(args):
	if not os.path.isfile(args.build_config):
		errString = f"Build config '{args.build_config}' was not a valid file."

		if args.build_config == DEFAULT_BUILD_CONFIG_NAME:
			errString += " Run with the --gen-config switch to generate a template config in the working directory."

		print(errString, file=sys.stderr)
		sys.exit(1)

	configObj = None

	with open(args.build_config, "r") as inFile:
		configObj = json.load(inFile)

	if configObj is None:
		print("Could not load build config", args.build_config, file=sys.stderr)
		sys.exit(1)

	if not os.path.isfile(configObj["arduinoCliPath"]):
		print("Arduino CLI path", configObj["arduinoCliPath"], "is not valid.", file=sys.stderr)
		sys.exit(1)

	configObj["buildType"] = args.build_type
	return configObj

def main():
	global currentBuildConfig

	args = parseArgs()
	validateArgs(args)

	if args.gen_config:
		generateSampleBuildConfig()
		sys.exit(1)

	currentBuildConfig = loadBuildConfig(args)
	print("Using build config:", args.build_config)

	initBuildDir()

	for command in args.cmds:
		print("*** Command:", command)

		if command == "compile":
			compile()
		elif command == "upload":
			upload()
		elif command == "clean":
			initBuildDir(True)


if __name__ == "__main__":
	main()
