# Packet Analizer


### Description 
The Ethernet source and destination address and the decoded Ethernet type.  
The source and destination IP (version 4 and 6) addresses, if appropriate.  
The source and destination ports for UDP and TCP.  
If the packet is TCP, then indicate when SYN or FIN flags are set.

### Usage
From Stream:  

    make; ./packets  

From File:  

    make; ./packets file.pcap