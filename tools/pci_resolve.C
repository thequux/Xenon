#include <stdio.h>
#include <stdlib.h>
extern "C" {
#include <pci/pci.h>
}
int main (int argc, char** argv) {
	int vendor = (int)strtol(argv[1], NULL, 16);
	int device = (int)strtol(argv[2], NULL, 16);

	char buf[512];
	pci_access* acc = pci_alloc();
	acc->numeric_ids = 0;
	acc->debugging = 0;
	acc->writeable = 0;
	acc->id_file_name = PCI_PATH_IDS;
	pci_init (acc);
	printf ("%s\n", pci_lookup_name(acc, buf,  512, PCI_LOOKUP_DEVICE, vendor, device));

	pci_cleanup(acc);
	return 0;
}
