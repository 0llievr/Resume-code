#include <pcap/pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <string.h>

/* Maximum time that the OS will buffer packets before giving them to your program. */
#define MAX_BUFFER_TIME_MS (300)

/* Maximum time the program will wait for a packet during live capture.
 * Measured in MAX_BUFFER_TIME_MS units. Program closes when it expires. */
#define MAX_IDLE_TIME 100 /* 100*MAX_BUFFER_TIME_MS idle time at most */

/* Function that creates the structures necessary to perform a packet capture and
 * determines capture source depending on arguments. Function will terminate the
 * program on error, so return value always valid. */
pcap_t *setup_capture(int argc, char *argv[], char *use_file);

/* Cleanup the state of the capture. */
void cleanup_capture(pcap_t *handle);

/* Check for abnormal conditions during capture.
 * 1 returned if a packet is ready, 0 if a packet is not available.
 * Terminates program if an unrecoverable error occurs. */
char valid_capture(int return_value, pcap_t *pcap_handle, char use_file);


int main(int argc, char *argv[])
{

    pcap_t *pcap_handle = NULL;            /* Handle for PCAP library */
    struct pcap_pkthdr *packet_hdr = NULL; /* Packet header from PCAP */
    const u_char *packet_data = NULL;      /* Packet data from PCAP */
    int ret = 0;                           /* Return value from library calls */
    char use_file = 0;                     /* Flag to use file or live capture */

    /* Setup the capture and get the valid handle. */
    pcap_handle = setup_capture(argc, argv, &use_file);

    /* Loop through all the packets in the trace file.
	 * ret will equal -2 when the trace file ends.
	 * ret will never equal -2 for a live capture. */
    ret = pcap_next_ex(pcap_handle, &packet_hdr, &packet_data);
    while (ret != -2)
    {
        if (valid_capture(ret, pcap_handle, use_file))
        {

            for (int i = 6; i < 12; i++){
                if (packet_data[i] == 0x00){
                    printf("0");
                }else{
                    printf("%x", (packet_data[i]));
                }if (i < 11){
                    printf(":");
                }
            }
            printf(" -> ");
            for (int i = 0; i < 6; i++){
                if (packet_data[i] == 0x00){
                    printf("0");
                }else{
                    printf("%x", (packet_data[i]));
                }if (i < 5){
                    printf(":");
                }
            }
            printf("\n");


            /*Checks the last four bytes of the ethernet header to determine which protocol is being run next */
            if (packet_data[12] == 0x08 && packet_data[13] == 0x00){
                printf("\t[IPv4] ");
                //Print the source address as an unsigned decimal value
                printf("%u.%u.%u.%u", packet_data[26], packet_data[27], packet_data[28], packet_data[29]);
                printf(" -> ");
                //Prints the destination address as an unsigned decimal value
                printf("%u.%u.%u.%u\n", packet_data[30], packet_data[31], packet_data[32], packet_data[33]);
                //Checks the the 23rd byte to see which protocl is running with IPv4, if it has a hex value of 06 then the protocol is TCP
                if (packet_data[23] == 0x06){
                    printf("\t[TCP] ");
                    printf("%u -> %u", packet_data[34] << 8 | packet_data[35], packet_data[36] << 8 | packet_data[37]);
                    /* Determines if flags have been set */
                    //Checks if syn flag has been set
                    if (packet_data[47] & 0b10){
                        printf(" SYN");
                    }
                    //Checks if fin flag has been set
                    else if (packet_data[47] & 0b01){
                        printf(" FIN");
                    }
                    //checks is both have been set
                    else if (packet_data[47] & 0b11){
                        printf(" FIN & SYN");
                    }
                    printf("\n");
                }
                //If the 23rd byte has a hex value equal to 11, if so then the protocol it is running is UDP.
                else if (packet_data[23] == 0x11){
                    printf("\t[UDP] ");
                    printf("%u -> %u\n", packet_data[34] << 8 | packet_data[35], packet_data[36] << 8 | packet_data[37]);
                }
                else{
                    printf("\t[%u]\n", packet_data[23]);
                }
            }


            /* If the last two bytes of the ethernet header are 86 DD, then the next protocol to run will be IPv6 */
            else if (packet_data[12] == 0x86 && packet_data[13] == 0xDD){
                printf("\t[IPv6] ");
                //source
                for (int i = 22; i < 36; i = i + 2){
                    if (packet_data[i] == 0x00 && packet_data[i + 1] == 0x00){
                        if (packet_data[i + 2] != 0x00 || packet_data[i + 3] != 0x00){ // if the next print is not 0000 put a :
                            printf(":");
                        }
                    }else if (packet_data[i] == 0x00 && packet_data[i + 1] != 0x00){
                        printf("%x:", packet_data[i + 1]);
                    }else{
                        printf("%x%02x:", packet_data[i], packet_data[i + 1]); //print
                    }
                }
                if (packet_data[36] == 0x00 && packet_data[37] != 0x00){
                    printf("%x -> ", packet_data[37]); //print the last one
                }else{
                    printf("%x%02x -> ", packet_data[36], packet_data[37]); //print the last one
                }

                //destination
                for (int i = 38; i < 51; i = i + 2){
                    if (packet_data[i] == 0x00 && packet_data[i + 1] == 0x00){ //if its 0000 dont print anything
                        if (packet_data[i + 2] != 0x00 || packet_data[i + 3] != 0x00){ // if the next print is not 0000 put a :
                            printf(":");
                        }
                    }else if (packet_data[i] == 0x00 && packet_data[i + 1] != 0x00){
                        printf("%x:", packet_data[i + 1]);
                    }else{
                        printf("%x%02x:", packet_data[i], packet_data[i + 1]); //print
                    }
                }
                if (packet_data[52] == 0x00 && packet_data[53] != 0x00){
                    printf("%x\n", packet_data[53]); //print the last one
                }else{
                    printf("%x%02x\n", packet_data[52], packet_data[53]); //print the last one
                }

                //print UDP or TCP
                if (packet_data[20] == 0x11){ //if UDP
                    printf("\t[UDP] %u -> %u\n", packet_data[54] << 8 | packet_data[55], packet_data[56] << 8 | packet_data[57]);
                }else if (packet_data[20] == 0x06){ //if TCP

                    printf("\t[TCP] %u -> %u", packet_data[54] << 8 | packet_data[55], packet_data[56] << 8 | packet_data[57]);

                    if (packet_data[67] & 0b01){
                        printf(" FIN");
                    }else if (packet_data[67] & 0b10){
                        printf(" SYN");
                    }else if (packet_data[67] & 0b10){
                        printf(" SYN & FIN");
                    }
                    printf("\n");
                }else{
                    printf("\t[%u]\n", packet_data[20]);
                }
            }
            else{
                printf("\t[%u]\n", packet_data[23]);
            }
        }
        /* Get the next packet */
        ret = pcap_next_ex(pcap_handle, &packet_hdr, &packet_data);
    }

    cleanup_capture(pcap_handle);
    return 0;
}

pcap_t *setup_capture(int argc, char *argv[], char *use_file){
    char *trace_file = NULL;          /* Trace file to process */
    pcap_t *pcap_handle = NULL;       /* Handle for PCAP library to return */
    char pcap_buff[PCAP_ERRBUF_SIZE]; /* Error buffer used by pcap functions */
    pcap_if_t *dev_list;              /* List of devices to open for live capture */
    pcap_if_t *dev_itr;               /* Iterator for device list */

    /* Check command line arguments */
    if (argc > 2){
        fprintf(stderr, "Usage: %s [trace_file]\n", argv[0]);
        exit(-1);
    }else if (argc > 1){
        *use_file = 1;
        trace_file = argv[1];
    }else{
        *use_file = 0;
    }

    /* Open the trace file, if appropriate */
    if (*use_file){
        pcap_handle = pcap_open_offline(trace_file, pcap_buff);
        if (pcap_handle == NULL)
        {
            fprintf(stderr, "Error opening trace file \"%s\": %s\n", trace_file, pcap_buff);
            exit(-1);
        }
    }
    /* Lookup and open the default device if trace file not used */
    else
    {
        if (pcap_findalldevs(&dev_list, pcap_buff))
        {
            fprintf(stderr, "Error finding capture device list: %s\n", pcap_buff);
            exit(-1);
        }

        /* No interfaces avaialble */
        if (dev_list == NULL)
        {
            fprintf(stderr, "No interfaces available for capture.\n");
            exit(-1);
        }

        /* Go through device list for suitable interface and open it */
        dev_itr = dev_list;
        while ((dev_itr != NULL) && (pcap_handle == NULL))
        {

            /* Skip loopback, down interfaces, and non-running interfaces */
            if (!(dev_itr->flags & PCAP_IF_LOOPBACK) && (dev_itr->flags & PCAP_IF_UP) && (dev_itr->flags & PCAP_IF_RUNNING)){

                /* Use buffer length as indication of warning, per pcap_open_live(3). */
                pcap_buff[0] = 0;

                pcap_handle = pcap_open_live(dev_itr->name, BUFSIZ, 1, MAX_BUFFER_TIME_MS, pcap_buff);
                if (pcap_handle == NULL){
                    fprintf(stderr, "Error opening capture device %s: %s\n", dev_itr->name, pcap_buff);
                    exit(-1);
                }
                if (pcap_buff[0] != 0){
                    printf("Warning: %s\n", pcap_buff);
                }
            }

            /* Try next device */
            if (pcap_handle == NULL){
                dev_itr = dev_itr->next;
            }
        }

        /* No suitable interfaces */
        if (dev_itr == NULL){
            fprintf(stderr, "No suitable interfaces available for capture.\n");
            exit(-1);
        }

        printf("Capturing on interface '%s'\n", dev_itr->name);

        pcap_freealldevs(dev_list);
    }

    return pcap_handle;
}

void cleanup_capture(pcap_t *handle){
    /* Close the trace file or device */
    pcap_close(handle);
}

char valid_capture(int return_value, pcap_t *pcap_handle, char use_file){
    static int idle_count = 0; /* Count of idle periods with no packets */
    char ret = 0;              /* Return value, invalid by default */

    /* A general error occurred */
    if (return_value == -1){
        pcap_perror(pcap_handle, "Error processing packet:");
        cleanup_capture(pcap_handle);
        exit(-1);
    }

    /* Timeout occured for a live packet capture */
    else if ((return_value == 0) && (use_file == 0)){
        if (++idle_count >= MAX_IDLE_TIME){
            printf("Timeout waiting for additional packets on interface\n");
            cleanup_capture(pcap_handle);
            exit(0);
        }
    }

    /* Unexpected/unknown return value */
    else if (return_value != 1){
        fprintf(stderr, "Unexpected return value (%i) from pcap_next_ex()\n", return_value);
        cleanup_capture(pcap_handle);
        exit(-1);
    }
    /* Normal operation, packet arrived */
    else{
        idle_count = 0;
        ret = 1;
    }

    return ret;
}