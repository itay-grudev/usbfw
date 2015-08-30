// Copyright (C) 2015 Itay Grudev <itay@grudev.com>
//
// This file is part of the USB Firewall.
// USB Firewall is free software:  you can redistribute it and/or modify it
// under the terms of the GNU General Public License version 3 as published
// by the Free Software Foundation.
//
// USB  Firewall  is distributed in the hope  that it will be  useful,  but
// WITHOUT ANY WARRANTY;  without even implied warranty of  MERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// version 3 for more details.
//
// You should have received a copy of the  GNU General Public License along
// with the software. If not, see <http://www.gnu.org/licenses/>.

#include <cstdio>
#include <string>
#include <cstring>

#define LOGFILE "/var/log/usbfw.log"

// Help and usage
void help();
void usage();

// Commands
int event(char*, char*, char*, char*);
int enable() { return 0; }
int disable() { return 0; }
int logging(int) { return 0; }
int allow(int, char*[]) { return 0; }
int deny(int, char*[]) { return 0; }
int limit(int, char*[]) { return 0; }
int delete_rule(int, char*[]) { return 0; }
int insert(int, char*[], bool) { return 0; }
int reload() { return 0; }
int status(int, char*[]) { return 0; }
int logs(int) { return 0; }
int version() { return 0; }

/**
 * @brief Debug mode flag.
 * If set, no actions are executed and everything that would have been done
 * is outputed with details on stdout;
 */
bool debug = false;

int main(int argc, char* argv[]) {

	// Anything less than 2 arguments is invalid
	if ( argc < 2 ) {
		usage();
		return 0;
	}

	for( int i = 1; i < argc; ++i ) {

		// Help and Usage flags
		if( strcmp(argv[i], "-h") == 0 ) {
			usage();
			return 0;
		}
		if ( strcmp(argv[i], "--help") == 0 ) {
			help();
			return 0;
		}
	}

	// Event processing command
	if ( strcmp(argv[1], "-e") == 0 ) { //			EVENT command
		if ( argc < 6 ) {
			usage();
			return 1;
		}
		return event(argv[2], argv[3], argv[4], argv[5]);
	} else if ( strcmp(argv[1], "help") == 0 ) { //			HELP    command
		help();
		return 0;
	} else if ( strcmp(argv[1], "enable") == 0 ) { //		ENABLE  command
		if( argc != 2 ) help();
		else return enable();
	} else if ( strcmp(argv[1], "disable") == 0 ) { //	DISABLE command
		if( argc != 2 ) help();
		else return disable();
	} else if ( strcmp(argv[1], "logging") == 0 ) { //	LOGGING command
		if( argc != 3 ) help();
		else return logging(std::stoi(argv[2]));
	} else if ( strcmp(argv[1], "allow") == 0 ) { //		ALLOW   command
		return allow(argc - 2, &argv[2]);
	} else if ( strcmp(argv[1], "deny") == 0 ) { //			DENY    command
		return deny(argc - 2, &argv[2]);
	} else if ( strcmp(argv[1], "limit") == 0 ) { //		LIMIT   command
		return limit(argc - 2, &argv[2]);
	} else if ( strcmp(argv[1], "delete") == 0 ) { //		DELETE  command
		return delete_rule(argc - 2, &argv[2]);
	} else if ( strcmp(argv[1], "insert") == 0 ) { //		INSERT  command
		return insert(argc - 2, &argv[2], true);
	} else if ( strcmp(argv[1], "reload") == 0 ) { //		RELOAD  command
		if( argc != 2 ) help();
		else return reload();
	} else if ( strcmp(argv[1], "status") == 0 ) { //		STATUS  command
		return status(argc - 2, &argv[2]);
	} else if ( strcmp(argv[1], "logs") == 0 ) { //			LOGS    command
		if( argc != 3 ) help();
		else return logs(std::stoi(argv[2]));
	} else if ( strcmp(argv[1], "version") == 0 ) { //	VERSION command
		if( argc != 2 ) help();
		else return version();
	}

	return 1;
}

int event(char* event, char* devpath, char* devnode, char* parent) {
	// Log either to stdout or to LOGFILE (in /var/log/)
	if( debug ) {
		printf("%s:\t%s\t%s\t%s\n", event, devpath, devnode, parent);
	} else {
		FILE *logfile = fopen(LOGFILE, "a");
		fprintf(logfile, "%s:\t%s\t%s\t%s\n", event, devpath, devnode, parent);
		fclose(logfile);
	}

	return 0;
}

void usage() {
	printf("Usage: usbfw [<command> [[ARG] ...]] "
		     "[-e <event> <devpath> <devnode> <parent> [-d]] [-h] [--help] \n");
}

void help() {
	printf("\n");
	usage();
	printf("\nCommands:\n"
				 "  enable\t\t Enable the firewall\n"
				 "  disable\t\t Disable the firewall\n"
				 "  logging LEVEL\t\t Set logging to LEVEL\n"
				 "  allow ARGS\t\t Add allow rule\n"
				 "  deny ARGS\t\t Add deny rule\n"
				 "  limit ARGS\t\t Add limit rule\n"
				 "  delete RULE|NUM\t Delete RULE\n"
				 "  insert NUM RULE\t Insert RULE at NUM\n"
				 "  reload\t\t Reload the firewall\n"
				 "  status\t\t Show firewall status\n"
				 "  status verbose\t Show verbose firewall status\n"
				 "  logs NUM\t\t Show the last NUM entries from the log\n"
				 "  version\t\t Display version information\n"
		     "\nEvents (These are only used by the system itself or for debugging):\n"
				 "  Use the \"-e\" flag instead of a command, followed by 4 arguments:\n"
				 "    <TYPE>\t\t The type of the event\n"
				 "    <DEVPATH>\t\t The device path as defined by udev\n"
				 "    <DEVNODE>\t\t The device node name as defined by udev\n"
				 "    <PARENT>\t\t The device node name of the parent if the device\n"
		     "  -d Toggles debug mode. Used for debugging events. This showes how\n"
				 "     the event will be processed without deauthorizing the device.\n"
				 "\nExamples:\n"
				 "  # Enable / Disable the firewall\n"
				 "  usbfw enable\n"
				 "  usbfw disable\n\n"
				 "  # Show verbose status of the firewall\n"
				 "  usbfw status verbose\n\n"
				 "  # Test an event without actually deauthorizing the device\n"
				 "  usbfw -e add DEVPATH DEVNODE PARENT -d\n");
	printf("\n");
}
