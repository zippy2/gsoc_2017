/*
 * Basic domain information
 *
 * This program fetches and prints out some information for given domain.
 * An example of invocation:
 *
 *   $ make exercise
 *   $ exercise qemu:///system myDomain
 *   Domain name:            test
 *   Domain state:           running
 *   Domain disks:           vda, vdb
 *   Domain interfaces:      vnet0
 *   Domain IP addresses:    192.168.122.2/24,fe80::5054:ff:fea4:6f91/64
 *
 * The first argument for the program is connection URI, the second argument is
 * domain name. Feel free to add whatever type of information you want.
 */

#include <stdio.h>
#include <stdlib.h>
#include <libvirt/libvirt.h>

/* TODO You may include C Standard Library headers and define additional
 * structs.
 */

#define VIRT_ERROR(...)                                         \
do {                                                            \
    fprintf(stderr, "ERROR %s:%d : ", __func__, __LINE__);      \
    fprintf(stderr, __VA_ARGS__);                               \
    fprintf(stderr, "\n");                                      \
} while (0)


/* getDomainState:
 * @dom: Domain pointer
 *
 * Returns stringified representation of domain state,
 * or NULL upon an error. */
const char *getDomainState(virDomainPtr dom)
{
    int state;
    const char *statesStr[] = {
        "nostate",
        "running",
        "blocked",
        "paused ",
        "shutdown",
        "shutoff",
        "crashed",
        "pmsuspended"
    };

    if (virDomainGetState(dom, &state, NULL, 0) < 0) {
        VIRT_ERROR("Unable to get domain state");
        return NULL;
    }

    return statesStr[state];
}


/* getDomainDisks:
 * @dom: Domain pointer
 *
 * For given domain return the list of disk targets delimited by
 * commas and spaces. For instance:
 *    "vda, vdb, sdc, sdd".
 *
 * If not applicable (domain has no disks), return an empty
 * string "".
 * The return value should be automatically allocated and caller
 * is responsible for freeing it. Should an error occur, a NULL
 * pointer is returned. */
char *
getDomainDisks(virDomainPtr dom)
{
    return NULL;
}


/* getDomainIfaces:
 * @dom: Domain pointer
 *
 * For given domain return the list of virtual interfaces
 * delimited by commas and spaces. For instance:
 *    "vnet0, vnet1, vnet2".
 *
 * If not applicable (domain has no interfaces), return an empty
 * string "".
 * The return value should be automatically allocated and caller
 * is responsible for freeing it. Should an error occur, a NULL
 * pointer is returned. */
char *
getDomainIfaces(virDomainPtr dom)
{
    return NULL;
}


/* getDomainIPs:
 * @dom: Domain pointer
 *
 * For given domain return the list of its IP addresses delimited
 * by commas and spaces. For instance:
 *    "192.168.122.2/24, 192.168.2.3/24, fe80::5054:ff:fea4:6f91/64".
 *
 * If not applicable (domain has no IP addresses), return an empty
 * string "". The list should be ordered, meaning IPv4 addresses
 * should go before IPv6 addresses. A single address is then
 * followed by '/' character and subnet length in bits.
 * The return value should be automatically allocated and caller
 * is responsible for freeing it. Should an error occur, a NULL
 * pointer is returned. */
char *
getDomainIPs(virDomainPtr dom)
{
    return NULL;
}


/* === DO NOT MODIFY ANYTHING BELOW THIS LINE === */
/*          except for adding a test case         */

/* Test harness */
int main(int argc, char **argv)
{
    int ret = EXIT_FAILURE;
    const char *uri = "test:///default";
    const char *domName = "test";
    const char *domState = NULL;
    char *domDisks = NULL;
    char *domIfaces = NULL;
    char *domIPs = NULL;
    virConnectPtr conn = NULL;
    virDomainPtr dom = NULL;

    if (argc > 1)
        uri = argv[1];

    if (!(conn = virConnectOpen(uri))) {
        fprintf(stderr, "Unable to connect to %s\n", uri);
        goto cleanup;
    }

    if (argc > 2)
        domName = argv[2];

    if (!(dom = virDomainLookupByName(conn, domName))) {
        fprintf(stderr, "Unable to look up domain %s\n", domName);
        goto cleanup;
    }

    /* Lets gather some information on selected domain */
    domState = getDomainState(dom);
    domDisks = getDomainDisks(dom);
    domIfaces = getDomainIfaces(dom);
    domIPs = getDomainIPs(dom);


    /* Now that we have all the information print it out */
    printf("Domain name:\t\t%s\n", domName);
    printf("Domain state:\t\t%s\n", domState);
    printf("Domain disks:\t\t%s\n", domDisks);
    printf("Domain interfaces:\t%s\n", domIfaces);
    printf("Domain IP addresses:\t%s\n", domIPs);

 cleanup:
    virDomainFree(dom);
    virConnectClose(conn);
    free(domIPs);
    free(domIfaces);
    free(domDisks);
    return ret;
}
